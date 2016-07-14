/*
   This NAND reading code should work with minor modification for
   NAND with these characteristics:
    * Large Page (mem size over 1Gbit)
    * x8 bit io bus (for x16 modify addressing schemas)

   CHANGELOG:
    20100930  cyphunk
    20120912  luca melette+cyphunk
    20140522  cyphunk
    20150908  gina hortenbach+cyphunk

   Before using change:
    * Teensy/Arduino pin definitions for how you have connected
      your target (breakout board)
    * Page/Block size for target chip
    * Turning on/off interactive mode

   Use interactive mode (the define below) to query the chips
   block size and ID. When interactive mode is on you can open
   the serial terminal and execute:

     > readid
     This will print the ID.

     > scan
     This will print the first 128 bytes of the first 512 pages

     > read page
     You can then provide a page number and size to dump.

   Once you feel satisfied that the code is working somewhat
   with your target, you can turn the INTERACTIVE mode off.
   Now when you connect the serial console you will get raw
   data. To record this as a binary blob you can try:

    Linux:
     stty -F /dev/ttyACM* 115200 -icrnl -imaxbel -opost -onlcr -isig -icanon -echo
     cat /dev/ttyACM* > dump
     tail -f dump | xxd -c 66 | cat
    OSX:
     stty -f /dev/tty.usb* 115200
     cat /dev/cu.usb* > dump
     tail -f dump | xxd -c 66 | cat -c

   The dump will start 10 seconds after loading the code.

   Do not use `screen -L /dev/tty.usb*` as it will interpret
   some bytes rather that log them.

   The raw output by default includes a 32 byte ASCII prefix
   before each block in the form of:

     printf("BLOCK %025lu\n", page)

   This can be useful when the dump includes some sort of
   virtualised blocking mechanism of the filesystem (such as
   with UBIFS). You can turn this off by commenting out the
   PRINTBLOCKIDENT define. However leaving it on helps debug
   the output as it  arrives. The checkblocksize.py can be
   used to monitor the dump.
*/

//#define INTERACTIVE
// invert the data portion of blocks (and not oob):
//#define INVERTDATA


#define PRINTBLOCKIDENT // 32 byte block prefix
// When monitoring dump in non-interactive mode the following commands have
// been used in the past:
//   stty -f /dev/tty.usb* 115200; cat /dev/cu.usb* > dump
//   tail -f dump | xxd -c 66 | cat -c
//   tail -100000f dump | xxd -c 66 | cat -n | awk '{printf "0x%04X", $1; $1=""; print $0}'
// Count number of blocks:
//   grep -c "BLOCK " dump


// DEFINE CHIP TARGET
// FOR K9F2G08X0M
//#define PAGESIZE 2112
//#define NUMPAGES 131072      // (2048*64) // num of blocks (2048) times pages per block (64)
// FOR K9F1G08U0C
//#define PAGESIZE 2112
//#define NUMPAGES 65536       //(1024*64) // num of blocks (1024) times pages per block (64)
// FOR NAND02G-B2D
//#define PAGESIZE 2112
//#define NUMPAGES (2048*64)   // num of blocks (2048) times pages per block (64)
// FOR NAND512W3A2S
//#define PAGESIZE 512         // without spare/oob data
//#define NUMPAGES 131072      // 0x20000 //(4096*32) // num of blocks (4096) times pages per block (32)
// FOR HY27UF082G2B
//#define PAGESIZE 2112
//#define NUMPAGES 131072      // (2048*64) // num of blocks (2038) times pages per block (64)
// FOR MT29F4G08ABBDAH4-IT_D
//#define PAGESIZE 2112
//#define NUMPAGES 262144        // (4096*64) // num of blocks (4096) times pages per block (64)
//Device ID:    2C AC 90 15 56
// FOR MT29F2G08AAD
//#define PAGESIZE 2112
//#define NUMPAGES 131072        // (2048*64)
// FOR MT29F1G08ABA
#define PAGESIZE 2112
#define NUMPAGES 65536       //(1024*64)
//Device ID: 2C F1 80 95 04

/*
  ADDING NEW CHIPS

  1. Define PAGESIZE and NUMPAGES
  Consult the general description of target chip to determine PAGESIZE.
  NUMPAGES will often be found in a diagram describing the layout of planes.
  This diagram may define "Number of blocks per device". That number *
  number of pages per block should give you the total number of pages.
  If it helps compare with example datasheets whose chips are defined above.

  2. Check ADDRESSING format
  The address to read from is typically larger than the IO bus so it is
  sent in blocks. The mask can be different for different chips. There is
  probably a few common formats which we have not defined yet. So compare
  the address format with other chips defined here in. For each chip there
  is a function for writing the address for that chip that is not used but
  can be checked for reference. Each chip will have a table/figure defining
  the address layout. You will then need to change the code in
  nand_read_page_lp() accordingly.

  Example comparison:

    * K9F1G08X0C
           Pins: io0  io1  io2  io3  io4  io5  io6  io7    MASK
      1st Cycle:  a0   a1   a2   a3   a4   a5   a6   a7    column & 0xFF
      2nd Cycle:  a8   a9  a10  a11  low  low  low  low    (column>>8) & 0x0F
      3rd Cycle: a12  a13  a14  a15  a16  a17  a18  a19    page_addr & 0xFF
      4th Cycle: a20  a21  a22  a23  a24  a25  a26  a27    (page_addr>>8) & 0xFF

    The currentcode add's a 5th cycle for page_addr if
    NUMPAGES*PAGESIZE > 0x8000000 //128<<20 = 128MiB

    * HY27UF082G2B (x8 bus)
           Pins: io0  io1  io2  io3  io4  io5  io6  io7    MASK
      1st Cycle:  a0   a1   a2   a3   a4   a5   a6   a7    column & 0xFF
      2nd Cycle:  a8   a9  a10  a11  low  low  low  low    (column>>8) & 0x0F
      3rd Cycle: a12  a13  a14  a15  a16  a17  a18  a19    page_addr & 0xFF
      4th Cycle: a20  a21  a22  a23  a24  a25  a26  a27    (page_addr>>8) & 0xFF
      5th Cycle: a28  low  low  low  low  low  low  low    (page_addr>>16) & 0x01

    * MT29F4G08ABBDAH4-IT_D
      NOTE the pin order of the table in doc is reversed (io7 first, io0 last)
      not important for comparison or operation of code. We have also changed
      the address names slightly.

      Actual doc:
           Pins: io0  io1  io2  io3  io4  io5  io6  io7    MASK
      1st Cycle:  c0   c1   c2   c3   c4   c5   c6   c7    column & 0xFF
      2nd Cycle:  c8   c9  c10  c11  low  low  low  low    (column>>8) & 0x0F
      3rd Cycle:  p1   p2   p3   p4   p5   p6   b6   b7    page_addr & 0xFF
      4th Cycle:  b8   b9  b10  b11  b12  b13  b14  b15    (page_addr>>8) & 0xFF
      5th Cycle: b17  b18  low  low  low  low  low  low    (page_addr>>8) & 0xFF
      c=column, p=page, b=block
      block addr concated with page addr = actual page addr
      if c11==1 c6..10 must be 0 (why?)

      How we compare this with the other chips
           Pins: io0  io1  io2  io3  io4  io5  io6  io7    MASK
      1st Cycle:  a0   a1   a2   a3   a4   a5   a6   a7    column & 0xFF
      2nd Cycle:  a8   a9  a10  a11  low  low  low  low    (column>>8) & 0x0F
      3rd Cycle: a12  a13  a14  a15  a16  a17  a18  a19    page_addr & 0xFF
      4th Cycle: a20  a21  a22  a23  a24  a25  a26  a27    (page_addr>>8) & 0xFF
      5th Cycle: a20  a21  low  low  low  low  low  low    (page_addr>>16) & 0x3

      current addressing code in nand_read_page_lp() will already handle this
      addressing scheme except for the odd c11==1 condition. If we really needed
      to take into account c11==1 (a11 above) the mask in this condition:
      1nd Cycle: if a11==1: column & 0x3F
      2nd Cycle: if a11==1: (column>>8) & 0x8

 */

// bit order: lowest i/o bit at io_pins[0]
//int io_pins[] = { PIN_B6 , PIN_B5 , PIN_B1 , PIN_B0 , PIN_F0 , PIN_F1 , PIN_F6 , PIN_F7  };
//int io_pins[] = { PIN_B0 , PIN_B1 , PIN_B2 , PIN_B3 , PIN_B4 , PIN_B5 , PIN_B6 , PIN_B7  }; // smp d
//int io_pins[] = { PIN_B0 , PIN_B6 , PIN_B5 , PIN_B4 , PIN_B3 , PIN_B7 , PIN_D2 , PIN_D3  }; // mit gina
int io_pins[] = { PIN_D0 , PIN_D1 , PIN_D2 , PIN_D3 , PIN_C4 , PIN_C5 , PIN_C6 , PIN_C7  }; // workshop
int io_pinslen = sizeof(io_pins)/sizeof(io_pins[0]);

//R/B READY BUSY
// The Ready/Busy output is an Open Drain pin that signals the state of the memory.
//RE READ ENABLE
// The RE input is the serial data-out control, and when active drives the data
// onto the I/O bus. Data is valid tREA after the falling edge of RE which also
// increments the internal column address counter by one.
//CE CHIP ENABLE
// This input controls the selection of the device.
//CLE COMMAND LATCH ENABLE
// This input activates the latching of the IO inputs inside the Command Register
// on the Rising edge of Write Enable  (WE).
//ALE ADDRESS LATCH ENABLE
// This input activates the latching of the IO inputs inside the Address Register
// on the Rising edge of Write Enable  (WE).
//WE WRITE ENABLE
// This input acts as clock to latch Command, Address and Data. The IO inputs are
// latched on the rise edge of WE.
//WP WRITE PROTECT
// The WP pin, when Low, provides an Hardware protection against undesired modify
// (program / erase) operations.
/*int RB  = PIN_C6;
int RE  = PIN_C1;
int CE  = PIN_C0;
int CLE = PIN_D7;
int ALE = PIN_D6;
int WE  = PIN_D1;
int WP  = PIN_D0;*/

int RB  = PIN_F0; // not connected actually
int RE  = PIN_F4;
int CE  = PIN_F3;
int CLE = PIN_B1;
int ALE = PIN_B0;
int WE  = PIN_B3;
int WP  = PIN_B2;

void p(char *fmt, ...);

void setup (void) {
  //pinMode(RB,  INPUT);
  pinMode(RE,  OUTPUT);
  pinMode(CE,  OUTPUT);
  pinMode(CLE, OUTPUT);
  pinMode(ALE, OUTPUT);
  pinMode(WE,  OUTPUT);
  pinMode(WP,  OUTPUT);

  //Serial.begin(9600);
  //Serial.begin(38400);

  // 230400 is the MAX i've been able to get with 16Mhz at 3.3v, and only when doubled from 115200
  Serial.begin(115200);
  //UCSR0A |= 2; //double the baud to 230400 - doesnt seem to work
  //Serial.begin(230400);
  //UCSR0A |= 2; //double the baud to 460800
  //Serial.begin(460800);
  //UCSR0A |= 2; //double the baud to 921600
  //Serial.begin(921600);
  //UCSR0A |= 2; //double the baud to 1843200
}

#define CMDLEN 20
char command[CMDLEN];
int dummy;
void loop () {
#ifdef INTERACTIVE
  if (Serial.available())
  {
    // READ COMMAND
    delay(5); // hoping read buffer is idle after 5 ms
    int i = 0;
    while (Serial.available() && i < CMDLEN-1)
      command[i++] = Serial.read();

    Serial.flush();
    command[i] = 0; // terminate string
    Serial.println(command); // echo back

    // EXECUTE COMMAND
    if (strcmp(command, "test") == 0 || strcmp(command, "t") == 0) {
      nand_status_verbose();
    }
    if (strcmp(command, "readid") == 0 || strcmp(command, "i") == 0) {
      nand_reset();
      nand_read_id();
    }
    if (strcmp(command, "readid noreset") == 0 || strcmp(command, "I") == 0) {
      p("doesnt work\n");
      nand_read_id();
    }
    if (strcmp(command, "status") == 0 || strcmp(command, "s") == 0) {
      nand_reset();
      nand_status();
    }
    if (strcmp(command, "status noreset") == 0 || strcmp(command, "S") == 0) {
      p("doesnt work\n");
      nand_status();
    }
    if (strcmp(command, "scan pages") == 0 || strcmp(command, "R") == 0) {
      for (uint32_t i=0; i<512 /*NUMPAGES*/; i++) {
        p("Page %lu: ",i);
        nand_reset();
        nand_read_page(i,0,128);
        p("\n");
      }
    }
    if (strcmp(command, "read page") == 0 || strcmp(command, "P") == 0) {
      Serial.println("Format of input command is important. '.' ends command.");
      Serial.println("   pageN.       Dumps full page");
      Serial.println("   pageN,size.  Dumps size bytes from page");
      Serial.println("        ,size.  Dumps size bytes from all pages");
      Serial.println("        ,size.  Dumps size bytes from all pages");
      Serial.println("             .  End");
      char page[20]="";
      char size[20]="";
      char *ptr = page;
      char c;
      while(1) {
        c = Serial.read();
        if (c >= '0' && c <= '9') {
          *ptr++=c;
        }
        else if (c == ',') {
          *ptr = 0;
          ptr = size;
          continue;
        }
        else if (c == '.') {
          *ptr = 0;
          nand_reset();
          if (strlen(page) > 0 && strlen(size) == 0) {
            p("> %s.\n", page);
            nand_read_page(atoi(page));
          }
          else if (strlen(page) > 0 && strlen(size) > 0) {
            p("> %lu,%lu.\n", atoi(page), atoi(size));
            nand_read_page(atoi(page),0,atoi(size));
          }
          else if (strlen(page) == 0 && strlen(size) > 0) {
            p("> ,%s.\n", size);
            for (uint32_t i=0; i<NUMPAGES;i++) {
              p("Page %lu: ",i);
              nand_read_page(i,0,atoi(size));
            }
          }
          ptr = size;
          *ptr = 0;
          ptr = page;
          *ptr = 0;
          p("\n> ");
        }
      }
    }
    Serial.print("\n> ");
  }
#else
  delay(10000);
  for (uint32_t i=0; i<NUMPAGES /*NUMPAGES*/; i++) {
        nand_reset();
        nand_read_page(i,0,PAGESIZE);
  }
  Serial.print("done");
  delay(0xFFFFFFFF);
#endif
}
