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
  //pinMode(btnX, INPUT_PULLUP);
  //pinMode(btnY, INPUT_PULLUP);
  //pinMode(btnSTART, INPUT_PULLUP);
  //pinMode(btnSELECT, INPUT_PULLUP);
  return;
}
