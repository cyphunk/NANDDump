
void printbin (int out) {
  int j;
  for (j=7; j>=0; j--) {
    if (out & (1 << j)) {
      Serial.print("1"); //49= "1"
    }
    else {
      Serial.print("0"); //48= "0"
    }
  }
}
/* printf. maxlength output of 128. cannot pass arguments twice*/
void p(char *fmt, ... )
{
  char tmp[128];
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  Serial.print(tmp);
}
/* set the global pin array to mode, with or without pullsups */
void io_pin_mode (uint8_t mode, uint8_t pullups)
{
  for (int i = 0; i < io_pinslen; i++) {
    pinMode(io_pins[i], mode);
    if (mode == INPUT && pullups == true)
      digitalWrite(io_pins[i], HIGH);
  }
}
void io_pin_mode (uint8_t mode)
{
  io_pin_mode(mode, false);
}
// 8bit
void io_write_byte(byte b)
{
  for (int i = 0; i < 8; i++) {
    digitalWrite(io_pins[i], (b >> i ) & 1 );
  }
}
byte io_read_byte()
{
  byte ret = 0;
  int val;
  for (int i = 0; i < 8; i++) {
    val = digitalRead(io_pins[i]);
    ret |= val << i;
  }
  return ret;
}
