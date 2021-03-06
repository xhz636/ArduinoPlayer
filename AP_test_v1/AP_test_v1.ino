#include <UTFT.h>
#include <SPI.h>
#include <SD.h>
#include <SimpleSDAudio.h>
#include "common.h"
#include "init.h"
#include "menu.h"
#include "book.h"
#include "button.h"
#include "music.h"
// Create static buffer 
#define BIGBUFSIZE (2*512)
uint8_t bigbuf[BIGBUFSIZE];
UTFT myGLCD(QD220A, A2, A1, A5, A4, A3);
File HZK, ASCII;
int work;  //当前所在位置
char workdirname[128];
int workdircase;
int main_menu_point, file_list_point, book_config_point;  //主菜单、文件菜单、电子书选项光标位置
int file_amount, file_offset;  //文件菜单中文件总量、文件偏移
char file_list[9][16];  //文件菜单列表
char book_name[32];  //电子书名
int txtfr, txtfg, txtfb, txtbr, txtbg, txtbb, txtdot;  //电子书前景、背景色及字号
uint32_t txt_now_offset, txt_next_offset, txt_max_offset;  //电子书文本相关偏移
int temp_r[2], temp_g[2], temp_b[2], temp_dot, temp_point;  //电子书选项中的临时前景、背景、字号和调色板光标
uint32_t temp_offset_rate;  //电子书选项中的临时偏移比例
boolean in_pallet;  //调色板标志
boolean txt_offset_changed;
char music_name[16];  //音乐名
boolean music_success;  //可播放音乐
int music_state, music_mode;  //播放状态、播放模式
int music_amount, music_offset;
char image_name[32];
int image_mode, image_state, image_temp_mode;
int image_left_offset, image_top_offset, image_temp_left_offset, image_temp_top_offset;
unsigned short image_width, image_height;
int image_width_insample, image_height_insample;
int image_point;
int image_amount, image_offset;
double image_sample;
char game_name[32];
int game_menu_point;
int game_clear_point;
volatile boolean game_playing;
uint32_t game_start_time, game_end_time;
int file_delete_point;
int about_menu_point, about_help_point;
const int btnUP = 9;
const int btnDOWN = 8;
const int btnLEFT = 7;
const int btnRIGHT = 6;
const int btnA = 5;
const int btnB = 4;
const int btnSTART = 3;
const int btnSELECT = 2;
const int battery = 10;
void setup()
{
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  pinMode(battery, OUTPUT);
  digitalWrite(battery, HIGH);
  myGLCD.InitLCD();
  myGLCD.InitLCD();//Initializes twice to improve reliability
  init_btn();  //初始化按钮
  if(!SD.begin(53))  //初始化SD卡
  {
    myGLCD.fillScr(255, 0, 0);
    return;
  }
  read_hz();  //连接字库
  init_music();  //初始化音乐功能
  show_apimg(0, 0, "sys/main.api");  //开机界面
  while(digitalRead(btnSTART) == HIGH)  //按START继续
    continue;
  show_main_menu();  //主菜单
}
void loop()
{
  press_button();  //检测按钮
  if(work == MUSIC_PLAY)
    check_music();
}
