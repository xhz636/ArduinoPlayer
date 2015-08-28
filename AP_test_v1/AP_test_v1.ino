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
int main_menu_point, file_list_point;
int file_amount, file_offset;
char file_list[9][16];
char book_name[32];
int txtfr, txtfg, txtfb, txtbr, txtbg, txtbb, txtdot;
uint32_t txt_last_offset, txt_now_offset, txt_next_offset, txt_max_offset;
const int btnUP = 2;
const int btnDOWN = 3;
const int btnLEFT = 4;
const int btnRIGHT = 5;
const int btnA = 6;
const int btnB = 7;
const int btnSTART = 8;
const int btnSELECT = 9;
void setup()
{
  randomSeed(analogRead(0));
  myGLCD.InitLCD();
  myGLCD.InitLCD();//Initializes twice to improve reliability
  init_btn();
  if(!SD.begin(53))
  {
    myGLCD.fillScr(255, 0, 0);
    return;
  }
  read_hz();
  show_apimg(0, 0, "sys/main.api");
  show_main_menu();
}
void loop()
{
  press_button();
}
