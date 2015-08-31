#include "common.h"
#include "init.h"
void read_hz()
{
  if(file_test("sys/HZK16"))
    HZK = SD.open("sys/HZK16");
  if(file_test("sys/ASCII"))
    ASCII = SD.open("sys/ASCII");
  return;
}
void init_btn()
{
  pinMode(btnUP, INPUT_PULLUP);
  pinMode(btnDOWN, INPUT_PULLUP);
  pinMode(btnLEFT, INPUT_PULLUP);
  pinMode(btnRIGHT, INPUT_PULLUP);
  pinMode(btnA, INPUT_PULLUP);
  pinMode(btnB, INPUT_PULLUP);
  pinMode(btnSTART, INPUT_PULLUP);
  pinMode(btnSELECT, INPUT_PULLUP);
  return;
}
void init_music()
{
  // Setting the buffer manually for more flexibility
  SdPlay.setWorkBuffer(bigbuf, BIGBUFSIZE);
  SdPlay.setSDCSPin(53);
  if (!SdPlay.init(SSDA_MODE_FULLRATE | SSDA_MODE_MONO | SSDA_MODE_AUTOWORKER))
    music_success = false;
  else
    music_success = true;
}

