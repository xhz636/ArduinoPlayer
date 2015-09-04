#include "common.h"
#include "game.h"
#include "menu.h"
#include "game_simulator.h"
#include "book.h"
void into_game(char* gamename)
{
  work = GAME_START;
  game_menu_point = 0;
  show_game_menu();
}
void exit_game()
{
  main_menu_point = 3;
  into_menu();
  return;
}
void show_game_menu()
{
  char gameicon[32];
  int left, top;
  myGLCD.fillScr(255, 255, 255);
  sprintf(gameicon, "%s/%s", game_name, "icon.api");
  read_image_size(gameicon);
  left = (220 - image_width) / 2;
  top = (89 - image_height) / 2;
  show_apimg(left, top, gameicon);
  show_chinese_sentence(78, 91, "\xBF\xAA\xCA\xBC\xD3\xCE\xCF\xB7", 0, 0, 0, 1);  //开始游戏
  show_chinese_sentence(78, 91 + 19, "\xB2\xE9\xBF\xB4\xBC\xC7\xC2\xBC", 0, 0, 0, 1);  //查看记录
  show_chinese_sentence(78, 91 + 19 * 2, "\xB2\xE9\xBF\xB4\xBD\xE9\xC9\xDC", 0, 0, 0, 1);  //查看介绍
  show_chinese_sentence(78, 91 + 19 * 3, "\xCD\xCB\xB3\xF6\xD3\xCE\xCF\xB7", 0, 0, 0, 1);  //退出游戏
  draw_game_menu_point(game_menu_point, 255, 0, 0);
}
void draw_game_menu_point(int point, int r, int g, int b)
{
  myGLCD.setColor(r, g, b);
  myGLCD.drawRect(76, 89 + 19 * point, 143, 108 + 19 * point);
}
void change_game_menu_point(int change)
{
  if(game_menu_point + change >= 0 && game_menu_point + change < 4)
  {
    draw_game_menu_point(game_menu_point, 255, 255, 255);
    game_menu_point += change;
    draw_game_menu_point(game_menu_point, 255, 0, 0);
    delay(200);
  }
}
void show_game_save()
{
  char savename[32];
  unsigned short play_count, win_count, lose_count;
  uint32_t play_time;
  unsigned char temp[10];
  int i;
  char data_temp[16];
  int rate, day, hour, minute, second;
  File entry;
  work = GAME_SAVE;
  sprintf(savename, "%s/%s", game_name, "save.aps");
  myGLCD.fillScr(255, 255, 255);
  if(!file_test(savename))
    return;
  entry = SD.open(savename);
  for(i = 0; i < 10; i++)
    temp[i] = entry.read();
  entry.close();
  play_count = *((unsigned short*)(&temp[0]));
  win_count = *((unsigned short*)(&temp[2]));
  lose_count = *((unsigned short*)(&temp[4]));
  play_time = *((uint32_t*)(&temp[6]));
  show_chinese_sentence(10, 38, "\xD3\xCE\xCF\xB7\xB4\xCE\xCA\xFD", 0, 0, 0, 1);  //游戏次数
  sprintf(data_temp, ":%hu", play_count);
  show_english(10 + 16 * 4, 38, data_temp, 0, 0, 0, 1);
  show_chinese_sentence(10, 58, "\xCA\xA4\xB3\xA1", 0, 0, 0, 1);  //胜场
  sprintf(data_temp, ":%hu", win_count);
  show_english(10 + 16 * 2, 58, data_temp, 0, 0, 0, 1);
  show_chinese_sentence(10, 78, "\xB0\xDC\xB3\xA1", 0, 0, 0, 1);  //败场
  sprintf(data_temp, ":%hu", lose_count);
  show_english(10 + 16 * 2, 78, data_temp, 0, 0, 0, 1);
  show_chinese_sentence(10, 98, "\xCA\xA4\xC2\xCA", 0, 0, 0, 1);  //胜率
  rate = win_count * 100 / play_count;
  sprintf(data_temp, ":%d%%", rate);
  show_english(10 + 16 * 2, 98, data_temp, 0, 0, 0, 1);
  show_chinese_sentence(10, 118, "\xCA\xB1\xBC\xE4", 0, 0, 0, 1);  //时间
  play_time /= 1000;
  second = play_time % 60;
  play_time /= 60;
  minute = play_time % 60;
  play_time /= 60;
  hour = play_time % 24;
  play_time /= 24;
  day = play_time;
  sprintf(data_temp, ":%02dd %02dh %02dm %02ds", day, hour, minute, second);
  show_english(10 + 16 * 2, 118, data_temp, 0, 0, 0, 1);
}
void show_game_help()
{
  char helpname[32];
  File entry;
  work = GAME_HELP;
  sprintf(helpname, "%s/%s", game_name, "help.txt");
  myGLCD.fillScr(255, 255, 255);
  if(!file_test(helpname))
    return;
  entry = SD.open(helpname);
  txt_max_offset = entry.size();
  entry.close();
  read_txt(helpname, 0, 0, 0, 0, 1);
}
