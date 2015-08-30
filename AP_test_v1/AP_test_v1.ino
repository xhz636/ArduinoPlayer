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
int work;  //当前所在位置
int main_menu_point, file_list_point, book_config_point;  //主菜单、文件菜单、电子书选项光标位置
int file_amount, file_offset;  //文件菜单中文件总量、文件偏移
char file_list[9][16];  //文件菜单列表
char book_name[32];  //电子书名
int txtfr, txtfg, txtfb, txtbr, txtbg, txtbb, txtdot;  //电子书前景、背景色及字号
uint32_t txt_last_offset, txt_now_offset, txt_next_offset, txt_max_offset;  //电子书文本相关偏移
int temp_r[2], temp_g[2], temp_b[2], temp_dot, temp_point;  //电子书选项中的临时前景、背景、字号和调色板光标
uint32_t temp_offset_rate;  //电子书选项中的临时偏移比例
boolean in_pallet;  //调色板标志
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
  //Serial.begin(9600);
  randomSeed(analogRead(0));
  myGLCD.InitLCD();
  myGLCD.InitLCD();//Initializes twice to improve reliability
  init_btn();  //初始化按钮
  if(!SD.begin(53))  //初始化SD卡
  {
    myGLCD.fillScr(255, 0, 0);
    return;
  }
  read_hz();  //连接字库
  show_apimg(0, 0, "sys/main.api");  //开机界面
  while(digitalRead(btnSTART) == HIGH)  //按START继续
    continue;
  show_main_menu();  //主菜单
}
void loop()
{
  press_button();  //检测按钮
}
