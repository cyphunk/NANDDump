
// FROM UBOOT drivers/mtd/nand_ids.c and nand.h
// Also http://git.infradead.org/mtd-www.git/tree/HEAD:/nand-data http://www.linux-mtd.infradead.org/nand-data/nanddata.html
/*
 * NAND Flash Manufacturer ID Codes
 */
// src: https://github.com/lentinj/u-boot/blob/415d386877df49eb051b85ef74fa59a16dc17c7d/include/linux/mtd/nand.h
#define NAND_MFR_TOSHIBA	0x98
#define NAND_MFR_SAMSUNG	0xec
#define NAND_MFR_FUJITSU	0x04
#define NAND_MFR_NATIONAL	0x8f
#define NAND_MFR_RENESAS	0x07
#define NAND_MFR_STMICRO	0x20
#define NAND_MFR_HYNIX		0xad
#define NAND_MFR_MICRON		0x2c
#define NAND_MFR_AMD		0x01
/**
 * struct nand_manufacturers - NAND Flash Manufacturer ID Structure
 * @name:	Manufacturer name
 * @id:		manufacturer ID code of device.
*/
struct nand_manufacturers {
	int id;
	char *name;
};
/*
*	Manufacturer ID list
*/
const struct nand_manufacturers nand_manuf_ids[] = {
	{NAND_MFR_TOSHIBA, "Toshiba"},
	{NAND_MFR_SAMSUNG, "Samsung"},
	{NAND_MFR_FUJITSU, "Fujitsu"},
	{NAND_MFR_NATIONAL, "National"},
	{NAND_MFR_RENESAS, "Renesas"},
	{NAND_MFR_STMICRO, "ST Micro"},
	{NAND_MFR_HYNIX, "Hynix"},
	{NAND_MFR_MICRON, "Micron"},
	{NAND_MFR_AMD, "AMD"},
	{0x0, "Unknown"}
};
/**
 * struct nand_flash_dev - NAND Flash Device ID Structure
 * @name:	Identify the device type
 * @id:		device ID code
 * @pagesize:	Pagesize in bytes. Either 256 or 512 or 0
 *		If the pagesize is 0, then the real pagesize
 *		and the eraseize are determined from the
 *		extended id bytes in the chip
 * @erasesize:	Size of an erase block in the flash device.
 * @chipsize:	Total chipsize in Mega Bytes
 * @options:	Bitfield to store chip relevant options
 */
struct nand_flash_dev {
	char *name;
	int id;
	unsigned long pagesize;
	unsigned long chipsize;
	unsigned long erasesize;
	unsigned long options;
};

/*
*	Chip ID list
*
*	Name. ID code, pagesize, chipsize in MegaByte, eraseblock size,
*	options
*
*	Pagesize; 0, 256, 512
*	0	get this information from the extended chip ID
+	256	256 Byte page size
*	512	512 Byte page size
*/
// src: https://github.com/lentinj/u-boot/blob/415d386877df49eb051b85ef74fa59a16dc17c7d/drivers/mtd/nand/nand_ids.c
const struct nand_flash_dev nand_flash_ids[] = {
        {"NAND 64MiB 3,3v 8-bit added by SRL", 0x20, 512, 64, 0x4000, 0}, // not sure what to put for erase size. 0x20000? if it is blocks in bytes including spare it would be 16896 0x4200. Lets assume it is without spare
//#ifdef CONFIG_MTD_NAND_MUSEUM_IDS
// IN OUR CASE IT MATCHES ONE OF THESE BUT IT IS NOT CORRECT SO WE LEAVE IT OUT. The Earase/Block Size is wrong should be 0x800
//	{"NAND 1MiB 5V 8-bit",		0x6e, 256, 1, 0x1000, 0},
//	{"NAND 2MiB 5V 8-bit",		0x64, 256, 2, 0x1000, 0},
//	{"NAND 4MiB 5V 8-bit",		0x6b, 512, 4, 0x2000, 0},
//	{"NAND 1MiB 3,3V 8-bit",	0xe8, 256, 1, 0x1000, 0},
//	{"NAND 1MiB 3,3V 8-bit",	0xec, 256, 1, 0x1000, 0}, // <--- this one
//	{"NAND 2MiB 3,3V 8-bit",	0xea, 256, 2, 0x1000, 0},
//	{"NAND 4MiB 3,3V 8-bit", 	0xd5, 512, 4, 0x2000, 0},
//	{"NAND 4MiB 3,3V 8-bit",	0xe3, 512, 4, 0x2000, 0},
//	{"NAND 4MiB 3,3V 8-bit",	0xe5, 512, 4, 0x2000, 0},
//	{"NAND 8MiB 3,3V 8-bit",	0xd6, 512, 8, 0x2000, 0},
//
//	{"NAND 8MiB 1,8V 8-bit",	0x39, 512, 8, 0x2000, 0},
//	{"NAND 8MiB 3,3V 8-bit",	0xe6, 512, 8, 0x2000, 0},
//	{"NAND 8MiB 1,8V 16-bit",	0x49, 512, 8, 0x2000, NAND_BUSWIDTH_16},
//	{"NAND 8MiB 3,3V 16-bit",	0x59, 512, 8, 0x2000, NAND_BUSWIDTH_16},
//#endif

	{"NAND 16MiB 1,8V 8-bit",	0x33, 512, 16, 0x4000, 0},
	{"NAND 16MiB 3,3V 8-bit",	0x73, 512, 16, 0x4000, 0},
//	{"NAND 16MiB 1,8V 16-bit",	0x43, 512, 16, 0x4000, NAND_BUSWIDTH_16},
//	{"NAND 16MiB 3,3V 16-bit",	0x53, 512, 16, 0x4000, NAND_BUSWIDTH_16},

	{"NAND 32MiB 1,8V 8-bit",	0x35, 512, 32, 0x4000, 0},
	{"NAND 32MiB 3,3V 8-bit",	0x75, 512, 32, 0x4000, 0},
//	{"NAND 32MiB 1,8V 16-bit",	0x45, 512, 32, 0x4000, NAND_BUSWIDTH_16},
//	{"NAND 32MiB 3,3V 16-bit",	0x55, 512, 32, 0x4000, NAND_BUSWIDTH_16},

	{"NAND 64MiB 1,8V 8-bit",	0x36, 512, 64, 0x4000, 0},
	{"NAND 64MiB 3,3V 8-bit",	0x76, 512, 64, 0x4000, 0},
//	{"NAND 64MiB 1,8V 16-bit",	0x46, 512, 64, 0x4000, NAND_BUSWIDTH_16},
//	{"NAND 64MiB 3,3V 16-bit",	0x56, 512, 64, 0x4000, NAND_BUSWIDTH_16},

	{"NAND 128MiB 1,8V 8-bit",	0x78, 512, 128, 0x4000, 0},
	{"NAND 128MiB 1,8V 8-bit",	0x39, 512, 128, 0x4000, 0},
	{"NAND 128MiB 3,3V 8-bit",	0x79, 512, 128, 0x4000, 0},
//	{"NAND 128MiB 1,8V 16-bit",	0x72, 512, 128, 0x4000, NAND_BUSWIDTH_16},
//	{"NAND 128MiB 1,8V 16-bit",	0x49, 512, 128, 0x4000, NAND_BUSWIDTH_16},
//	{"NAND 128MiB 3,3V 16-bit",	0x74, 512, 128, 0x4000, NAND_BUSWIDTH_16},
//	{"NAND 128MiB 3,3V 16-bit",	0x59, 512, 128, 0x4000, NAND_BUSWIDTH_16},

	{"NAND 256MiB 3,3V 8-bit",	0x71, 512, 256, 0x4000, 0},

	/*
	 * These are the new chips with large page size. The pagesize and the
	 * erasesize is determined from the extended id bytes
	 */
//#define LP_OPTIONS (NAND_SAMSUNG_LP_OPTIONS | NAND_NO_READRDY | NAND_NO_AUTOINCR)
//#define LP_OPTIONS16 (LP_OPTIONS | NAND_BUSWIDTH_16)
#define LP_OPTIONS 1

	/*512 Megabit */
	{"NAND 64MiB 1,8V 8-bit",	0xA2, 0,  64, 0, LP_OPTIONS},
	{"NAND 64MiB 1,8V 8-bit",	0xA0, 0,  64, 0, LP_OPTIONS},
	{"NAND 64MiB 3,3V 8-bit",	0xF2, 0,  64, 0, LP_OPTIONS},
	{"NAND 64MiB 3,3V 8-bit",	0xD0, 0,  64, 0, LP_OPTIONS},
//	{"NAND 64MiB 1,8V 16-bit",	0xB2, 0,  64, 0, LP_OPTIONS16},
//	{"NAND 64MiB 1,8V 16-bit",	0xB0, 0,  64, 0, LP_OPTIONS16},
//	{"NAND 64MiB 3,3V 16-bit",	0xC2, 0,  64, 0, LP_OPTIONS16},
//	{"NAND 64MiB 3,3V 16-bit",	0xC0, 0,  64, 0, LP_OPTIONS16},

	/* 1 Gigabit */
	{"NAND 128MiB 1,8V 8-bit",	0xA1, 0, 128, 0, LP_OPTIONS},
	{"NAND 128MiB 3,3V 8-bit",	0xF1, 0, 128, 0, LP_OPTIONS},
	{"NAND 128MiB 3,3V 8-bit",	0xD1, 0, 128, 0, LP_OPTIONS},
//	{"NAND 128MiB 1,8V 16-bit",	0xB1, 0, 128, 0, LP_OPTIONS16},
//	{"NAND 128MiB 3,3V 16-bit",	0xC1, 0, 128, 0, LP_OPTIONS16},
//	{"NAND 128MiB 1,8V 16-bit",     0xAD, 0, 128, 0, LP_OPTIONS16},

	/* 2 Gigabit */
	{"NAND 256MiB 1,8V 8-bit",	0xAA, 0, 256, 0, LP_OPTIONS},
	{"NAND 256MiB 3,3V 8-bit",	0xDA, 0, 256, 0, LP_OPTIONS},
//	{"NAND 256MiB 1,8V 16-bit",	0xBA, 0, 256, 0, LP_OPTIONS16},
//	{"NAND 256MiB 3,3V 16-bit",	0xCA, 0, 256, 0, LP_OPTIONS16},

	/* 4 Gigabit */
	{"NAND 512MiB 1,8V 8-bit",	0xAC, 0, 512, 0, LP_OPTIONS},
	{"NAND 512MiB 3,3V 8-bit",	0xDC, 0, 512, 0, LP_OPTIONS},
//	{"NAND 512MiB 1,8V 16-bit",	0xBC, 0, 512, 0, LP_OPTIONS16},
//	{"NAND 512MiB 3,3V 16-bit",	0xCC, 0, 512, 0, LP_OPTIONS16},

	/* 8 Gigabit */
	{"NAND 1GiB 1,8V 8-bit",	0xA3, 0, 1024, 0, LP_OPTIONS},
	{"NAND 1GiB 3,3V 8-bit",	0xD3, 0, 1024, 0, LP_OPTIONS},
//	{"NAND 1GiB 1,8V 16-bit",	0xB3, 0, 1024, 0, LP_OPTIONS16},
//	{"NAND 1GiB 3,3V 16-bit",	0xC3, 0, 1024, 0, LP_OPTIONS16},

	/* 16 Gigabit */
	{"NAND 2GiB 1,8V 8-bit",	0xA5, 0, 2048, 0, LP_OPTIONS},
	{"NAND 2GiB 3,3V 8-bit",	0xD5, 0, 2048, 0, LP_OPTIONS},
//	{"NAND 2GiB 1,8V 16-bit",	0xB5, 0, 2048, 0, LP_OPTIONS16},
//	{"NAND 2GiB 3,3V 16-bit",	0xC5, 0, 2048, 0, LP_OPTIONS16},

	/* 32 Gigabit */
	{"NAND 4GiB 1,8V 8-bit",	0xA7, 0, 4096, 0, LP_OPTIONS},
	{"NAND 4GiB 3,3V 8-bit",	0xD7, 0, 4096, 0, LP_OPTIONS},
//	{"NAND 4GiB 1,8V 16-bit",	0xB7, 0, 4096, 0, LP_OPTIONS16},
//	{"NAND 4GiB 3,3V 16-bit",	0xC7, 0, 4096, 0, LP_OPTIONS16},

	/* 64 Gigabit */
	{"NAND 8GiB 1,8V 8-bit",	0xAE, 0, 8192, 0, LP_OPTIONS},
	{"NAND 8GiB 3,3V 8-bit",	0xDE, 0, 8192, 0, LP_OPTIONS},
//	{"NAND 8GiB 1,8V 16-bit",	0xBE, 0, 8192, 0, LP_OPTIONS16},
//	{"NAND 8GiB 3,3V 16-bit",	0xCE, 0, 8192, 0, LP_OPTIONS16},

	/* 128 Gigabit */
	{"NAND 16GiB 1,8V 8-bit",	0x1A, 0, 16384, 0, LP_OPTIONS},
	{"NAND 16GiB 3,3V 8-bit",	0x3A, 0, 16384, 0, LP_OPTIONS},
//	{"NAND 16GiB 1,8V 16-bit",	0x2A, 0, 16384, 0, LP_OPTIONS16},
//	{"NAND 16GiB 3,3V 16-bit",	0x4A, 0, 16384, 0, LP_OPTIONS16},

	/* 256 Gigabit */
	{"NAND 32GiB 1,8V 8-bit",	0x1C, 0, 32768, 0, LP_OPTIONS},
	{"NAND 32GiB 3,3V 8-bit",	0x3C, 0, 32768, 0, LP_OPTIONS},
//	{"NAND 32GiB 1,8V 16-bit",	0x2C, 0, 32768, 0, LP_OPTIONS16},
//	{"NAND 32GiB 3,3V 16-bit",	0x4C, 0, 32768, 0, LP_OPTIONS16},

	/* 512 Gigabit */
	{"NAND 64GiB 1,8V 8-bit",	0x1E, 0, 65536, 0, LP_OPTIONS},
	{"NAND 64GiB 3,3V 8-bit",	0x3E, 0, 65536, 0, LP_OPTIONS},
//	{"NAND 64GiB 1,8V 16-bit",	0x2E, 0, 65536, 0, LP_OPTIONS16},
//	{"NAND 64GiB 3,3V 16-bit",	0x4E, 0, 65536, 0, LP_OPTIONS16},

	/*
	 * Renesas AND 1 Gigabit. Those chips do not support extended id and
	 * have a strange page/block layout !  The chosen minimum erasesize is
	 * 4 * 2 * 2048 = 16384 Byte, as those chips have an array of 4 page
	 * planes 1 block = 2 pages, but due to plane arrangement the blocks
	 * 0-3 consists of page 0 + 4,1 + 5, 2 + 6, 3 + 7 Anyway JFFS2 would
	 * increase the eraseblock size so we chose a combined one which can be
	 * erased in one go There are more speed improvements for reads and
	 * writes possible, but not implemented now
	 */
//	{"AND 128MiB 3,3V 8-bit",	0x01, 2048, 128, 0x4000,
//	 NAND_IS_AND | NAND_NO_AUTOINCR |NAND_NO_READRDY | NAND_4PAGE_ARRAY |
//	 BBT_AUTO_REFRESH
//	},

	{NULL,}
};






#define NAND_CMD_READID		0x90
#define NAND_CMD_RESET		0xff
#define NAND_CMD_STATUS		0x70
#define NAND_CMD_READ0		0
#define NAND_CMD_READ1		1 // For READ0 on Small Page targets.
#define NAND_CMD_READSTART	0x30
#define NAND_CMD_READOOB	0x50 // for READ0 on Small Page targets, to access OOB
void delay_test() {
  return;
  // for debugging
  delayMicroseconds(100);
}

byte nand_read_byte()
{
  // Assumes ALE/CLE low (off). CE high (on)
  io_pin_mode(INPUT); // overhead but oh well
  delay_test();
  byte ret;
  digitalWrite(WE,  HIGH); // write off
  delay_test();
  digitalWrite(RE,  LOW); // (active on falling edge)
  delay_test();
  ret = io_read_byte();
  delay_test();
  digitalWrite(RE,  HIGH);
  delay_test();
  return ret;
}
void nand_write_byte(byte b)
{
  io_pin_mode(OUTPUT); // overhead but oh well
  digitalWrite(RE, HIGH); // read off
  digitalWrite(WE,  LOW);
  io_write_byte(b);
  digitalWrite(WE,  HIGH);
}
/* this is close to the nand_command_lp() in u-boot nand_base.c */
void nand_command_lp(byte command, int16_t column, int32_t page_addr)
{
  digitalWrite(CLE, HIGH);
  nand_write_byte(command);
  digitalWrite(CLE, LOW);

  if (column != -1) { // I REALLy am  not sure that it is okay to use this like this
    digitalWrite(ALE, HIGH);
    nand_write_byte( column     & 0xFF);
    nand_write_byte((column>>8) & 0xFF);
    if (page_addr != -1) {
      nand_write_byte(  (page_addr)     & 0xFF);
      nand_write_byte(  (page_addr>>8)  & 0xFF);
      if (NUMPAGES*PAGESIZE > 0x8000000 /*128<<20 = 128MiB*/)
        nand_write_byte((page_addr>>16) & 0xFF); //BUGBUG with function argument. signed,unsigned
    }
    digitalWrite(ALE, LOW);
  }
}
void nand_reset ()
{
  digitalWrite(CE,  LOW); // chip  on
  delay(10);
  io_pin_mode(OUTPUT);
  // default state:
  digitalWrite(WP,  LOW); // X
  digitalWrite(ALE, LOW);  // addr off
  digitalWrite(RE,  HIGH); // read off
  digitalWrite(CE,  LOW);  // chip on
  digitalWrite(WE,  LOW); // write off

  digitalWrite(CLE, HIGH);
  nand_write_byte(NAND_CMD_RESET);
  digitalWrite(CLE, LOW); // CLE off

  delayMicroseconds(500); // tRST = Device Resetting Time (Read/Program/Erase) = max 500us
}

byte maf_id, dev_id, cellinfo, extid, reserved;
uint32_t writesize, erasesize;
uint16_t oobsize, buswidth;

void nand_read_id ()
{
  //io_write_byte(0x00); // not required. was suggested by someone online that looked at some nand chips
  delay(10);
  digitalWrite(CE,  LOW); // chip  on

//  nand_command_lp(NAND_CMD_READID, 0x00, -1);
  nand_command_lp(NAND_CMD_READID, -1, -1);
  digitalWrite(ALE, HIGH);
  nand_write_byte(0x00);
  digitalWrite(ALE, LOW);

  maf_id = nand_read_byte(); // maker code
  dev_id = nand_read_byte(); // device code

    // UBOOT nand_base.c nand_get_flash_type() suggest repeating:
  /* Try again to make sure, as some systems the bus-hold or other
   * interface concerns can cause random data which looks like a
   * possibly credible NAND flash to appear. If the two results do
   * not match, ignore the device completely.
   */
//  nand_command_lp(NAND_CMD_READID, 0x00, -1);
  nand_command_lp(NAND_CMD_READID, -1, -1);
  digitalWrite(ALE, HIGH);
  delay_test();
  nand_write_byte(0x00);
  delay_test();
  digitalWrite(ALE, LOW);
  delay_test();
  byte maf_verify = nand_read_byte(); // maker code
  byte dev_verify = nand_read_byte(); // device code
  if (maf_verify != maf_id || dev_verify != dev_id) {
    p("second ID read did not match "
      "%02x,%02x against %02x,%02x\n", maf_id, dev_id, maf_verify, dev_verify);
    digitalWrite(CE,  HIGH); // chip  off
    return;
  }
  cellinfo = nand_read_byte(); // 3rd
  extid    = nand_read_byte(); // 4th
  reserved = nand_read_byte(); // 5th
  p("Your device ID:   %02X %02X %02X %02X %02X \n", maf_id, dev_id, cellinfo, extid, reserved);
  p("\ntested...\n");
  p("K9F2G08X0M:       EC DA 80 15 50\n");
  p("NAND02GW3B2D:     20 DA 10 95 44\n");
  p("HY27UF082G2B:     AD DA 10 95 44\n");
  p("NAND512W3A2S:     20 76\n");
  p("\nvia docs...\n");
  p("K9F1G08U0C:       EC F1 00 95 40\n");
  p("K9F2G08U0M:       EC DA 80 15\n");
  p("K9F2G16U0M:       EC CA 80 55\n");
  p("K9F2G08U0C:       EC DA 10 15 44\n");


  const nand_flash_dev *type = nand_flash_ids;
  for (; type->name != NULL; type++)
    if (maf_id == type->id)
      break;
  const nand_manufacturers *maf = nand_manuf_ids;
  for (; maf->id != 0; maf++)
    if (maf_id == maf->id)
      break;

  p("\nExtended details\n");
  p("%s: %s\n\n", maf->name, type->name);

  printbin(extid); p(" Extid (4thbyte %02X):\n", extid);

  if (!type->pagesize) {
    /* Calc pagesize */
    writesize = 1024 << (extid & 0x03);
    extid >>= 2;
    /* Calc oobsize */
    oobsize = (8 << (extid & 0x01)) * (writesize >> 9);
    extid >>= 2;
    /* Calc blocksize. Blocksize is multiples of 64KiB */
    //erasesize = (64 * 1024) << (extid & 0x03);
    erasesize = 65536 << (extid & 0x03); // on AVR 64*1024=1 instead of 65536
    extid >>= 2;
    /* Get buswidth information */
    buswidth = (extid & 0x01) ? 16 : 8;
    p("  Pagesize %lu bytes + OBB %u\n", writesize, oobsize);
    p("  Blocksize %lu bytes (%uKB)\n", erasesize, erasesize/1024);
    p("  Buswidth %u bits\n", buswidth);
  }
  else {
    erasesize = type->erasesize;
    writesize = type->pagesize;
    //oobsize = type->writesize / 32;
    buswidth = 8; // only supporting 8 bit atm.  type->options & NAND_BUSWIDTH_16;
	p("  Pagesize %lu bytes\n", writesize);
	p("  Blocksize %lu bytes (%uKB)\n", erasesize, erasesize/1024);
	p("  Buswidth %u bits\n", buswidth);
  }
  digitalWrite(CE,  HIGH); // chip  off
}

void nand_status ()
{
  io_pin_mode(OUTPUT);
  digitalWrite(CE,  LOW); // chip  o
  delay(10);

  digitalWrite(CLE, HIGH);
  nand_write_byte(NAND_CMD_STATUS);
  digitalWrite(CLE, LOW);

  io_pin_mode(INPUT);
  int input[5];
  input[0] = nand_read_byte();

  p(" 0x%02x\n", input[0]);
  printbin(input[0]);

  digitalWrite(CE,  HIGH); // chip  off
}
void nand_status_verbose ()
{
  printbin(NAND_CMD_STATUS);
  io_pin_mode(OUTPUT);
  digitalWrite(CE,  LOW); // chip  o
  delay(10);

  digitalWrite(CLE, HIGH);
  nand_write_byte(NAND_CMD_STATUS);
  digitalWrite(CLE, LOW);

  io_pin_mode(INPUT);
  int input[5];
  input[0] = nand_read_byte();

  p(" 0x%02x\n", input[0]);
  printbin(input[0]);

  digitalWrite(CE,  HIGH); // chip  off
}

// DETAILS FOR K9F2G08X0M
// 1 page   is 2112   bytes
// 1 block  is 64     pages... hence
// 1 block  is 135168 bytes
// Total blocks = 2048
// Total pages  = 131072
// Total bytes  = 276824064 2Mbits
// Address size for cols is 12bit (4096)
// Address size for rows is 17bit
void   K9F2G08X0M_write_addr (uint32_t page, uint16_t col)
{
  p("addr %i,%i\n", page, col);
  nand_write_byte(col & 0xFF);
  nand_write_byte((col>>8) & 0xF);
  nand_write_byte(page & 0xFF);
  nand_write_byte((page>>8) & 0xFF);
  nand_write_byte((page>>16) & 0x1);
}

// DETAILS FOR K9F1G08U0C
//(2K+64)Byte 2048+64 2112  page size
//(128K+4K)Byte 1024*128+(1024*4) 135168  block size
// 1 page   is 2112   bytes (2048+64)
// 1 block  is 64     pages... hence
// 1 block  is 135168 bytes
// Total blocks = 1024
// Total pages  = 65536 (1024*64) <
// Total bytes  = 138412032 1Mbits
// addressing:
// "row" = page
// "col" = byte in row
// Address size for cols is 12bits (4096) enough for 2112
// Address size for rows is 16bits (65536) enough for all pages.
// read operations are page basis
void   K9F1G08U0C_write_addr (uint32_t page, uint16_t col)
{
  nand_write_byte(col & 0xFF);
  nand_write_byte(col>>8 & 0xF );
  nand_write_byte(page & 0xFF);
  nand_write_byte(page>>8 & 0xFF);
}
// DETAILS FOR NAND02G-B2D 8BIT
// 1 page   is 2112   bytes (2048+64)
// 1 block  is 64     pages... hence
// 1 block  is 135168 bytes
// Total blocks = 2048
// Total pages  = 131072 (2048*64) <
// Total bytes  = 276824064 2Gbits
// addressing VERY DIFFERNT but probably works just as well
// Address size for cols is 12bit (4096)
// Address size for rows is 17bit
void   NAND02GB2D_write_addr (uint32_t page, uint16_t col)
{
  nand_write_byte(col & 0xFF);
  nand_write_byte((col>>8) & 0xF);
  nand_write_byte(page & 0xFF);
  nand_write_byte((page>>8) & 0xFF);
  nand_write_byte((page>>16) & 0x1);
}
// DETAILS FOR NAND512W3A2S
// 1 page   is 528    bytes (512+16)
// 1 block  is 32     pages... hence
// 1 block  is 16896  bytes (without oob
// Total blocks = 4096
// Total pages  = 131072 (4096*32)
// Total bytes  = 69206016 512Mbits (4096*32*528)
// addressing:
// Address size for cols is
// Address size for rows is
void   NAND512W3A2S_write_addr (uint32_t page, uint16_t col)
{
  nand_write_byte(col & 0xFF);
  col>>=1; // the 9th bit gets send in the command before address!!
  nand_write_byte((col>>8) & 0xFF);
  nand_write_byte(page & 0xFF);
  nand_write_byte((page>>8) & 0x1);
}

void nand_read_page(uint32_t page, uint16_t col, uint16_t size)
{
  digitalWrite(CE,  LOW); // chip  on
  delay(1);

  nand_command_lp(NAND_CMD_READ0, col, page);
  nand_command_lp(NAND_CMD_READSTART, -1, -1);

  int thresh=150; // will wait 150*10, aka 1.5 milisecond
  while (digitalRead(RB) && thresh--) delayMicroseconds(1); // loop until RB=LOW, ready
  delayMicroseconds(25); // tR = Data Transfer from Cell to Register tR = 25us max

  byte input[PAGESIZE];
  for (int i=0; i<size; i++) {
    //if (i % 50 == 0) p("\n"); p(".");
    input[i] = nand_read_byte(); //delayMicroseconds(1);
#ifdef INVERTDATA
    if (col < 2048)
      input[i] = 255 - input[i];
#endif
  }

#ifdef INTERACTIVE
  //p("\nDone reading %u bytes from page %lu \n", size, page);
  for (uint16_t i=0; i<size; i++) {
    //if (i % 16 == 0)
      //Serial.println();
    //p("%02x ", input[i]);
    if ( (input[i] >= 32 && input[i] <= 126) || input[i] == 9/*\t*/|| input[i] == 10/*\n*/ || input[i] == 13/*\n*/ ) // only check printable text
      p("%c", input[i]);
    //else
    //  p("  ");
  }
  p("\n");
#else
#ifdef PRINTBLOCKIDENT
  p("BLOCK %025lu\n", page); // prints a marking of exactly 32 bytes (including \n)
#endif
  for (uint16_t i=0; i<size; i++) {
    Serial.print(input[i], BYTE);
  }
#endif

  digitalWrite(CE,  HIGH); // chip  off
}
void nand_read_page(uint32_t page, uint16_t col)
{
  nand_read_page(page, col, PAGESIZE);
}
void nand_read_page(uint32_t page)
{
  nand_read_page(page, 0, PAGESIZE);
}
