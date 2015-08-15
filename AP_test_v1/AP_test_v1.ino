#include <UTFT.h>
#include <SPI.h>
#include <SD.h>
#include "common.h"
#include "init.h"
#include "main_menu.h"
#include "book.h"
#include "button.h"
UTFT myGLCD(QD220A, A2, A1, A5, A4, A3);
File HZK, ASCII;
int work;
int main_menu_point;
uint32_t txt_last_offset, txt_now_offset, txt_next_offset;
const int btnUP = 5;
const int btnDOWN = 6;
const int btnLEFT = 7;
const int btnRIGHT = 8;
const int btnA = 2;
const int btnB = 3;
//const int btnX;
//const int btnY;
//const int btnSTART;
//const int btnSELECT;
void setup()
{
  uint32_t txtp;
  int i;
  randomSeed(analogRead(0));
  myGLCD.InitLCD();
  myGLCD.InitLCD();//Initializes twice to improve reliability
  if(!SD.begin(4))
  {
    myGLCD.fillScr(255, 0, 0);
    return;
  }
  init_btn();
  read_hz();
  show_apimg(0, 0, "sys/main.api");
  show_main_menu();
}
void loop()
{
  press_button();
}
