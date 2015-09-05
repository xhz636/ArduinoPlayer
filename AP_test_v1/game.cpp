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
  unsigned short play_count, win_count, lose_count, run_count;
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
  show_chinese_sentence(10, 18, "\xD3\xCE\xCF\xB7\xB4\xCE\xCA\xFD", 0, 0, 0, 1);  //游戏次数
  sprintf(data_temp, ":%hu", play_count);
  show_english(10 + 16 * 4, 18, data_temp, 0, 0, 0, 1);
  show_chinese_sentence(10, 38, "\xCA\xA4\xB3\xA1", 0, 0, 0, 1);  //胜场
  sprintf(data_temp, ":%hu", win_count);
  show_english(10 + 16 * 2, 38, data_temp, 0, 0, 0, 1);
  show_chinese_sentence(10, 58, "\xB0\xDC\xB3\xA1", 0, 0, 0, 1);  //败场
  sprintf(data_temp, ":%hu", lose_count);
  show_english(10 + 16 * 2, 58, data_temp, 0, 0, 0, 1);
  show_chinese_sentence(10, 78, "\xCC\xD3\xC5\xDC", 0, 0, 0, 1);  //逃跑
  run_count = play_count - win_count - lose_count;
  sprintf(data_temp, ":%hu", run_count);
  show_english(10 + 16 * 2, 78, data_temp, 0, 0, 0, 1);
  show_chinese_sentence(10, 98, "\xCA\xA4\xC2\xCA", 0, 0, 0, 1);  //胜率
  if(play_count != 0)
  {
    rate = win_count * 100 / play_count;
    sprintf(data_temp, ":%d%%", rate);
  }
  else
    sprintf(data_temp, ":?");
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
void show_clear()
{
  work = GAME_CLEAR;
  show_chinese_sentence(10, 138, "\xC7\xE5\xB3\xFD\xCA\xFD\xBE\xDD\xA3\xBF ", 0, 0, 0, 1);  //清除数据？
  show_chinese_sentence(10 + 16 * 5 + 8, 138, "\xB7\xF1", 0, 0, 0, 1);  //否
  show_chinese_sentence(10 + 16 * 7, 138, "\xCA\xC7", 0, 0, 0, 1);  //是
  game_clear_point = 0;
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRect(96, 136, 115, 155);
}
void choose_no_clear()
{
  if(game_clear_point != 0)
  {
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRect(120, 136, 139, 155);
    game_clear_point = 0;
    myGLCD.setColor(255, 0, 0);
    myGLCD.drawRect(96, 136, 115, 155);
  }
}
void choose_yes_clear()
{
  if(game_clear_point == 0)
  {
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRect(96, 136, 115, 155);
    game_clear_point = 1;
    myGLCD.setColor(255, 0, 0);
    myGLCD.drawRect(120, 136, 139, 155);
  }
}
void clear_save()
{
  File entry;
  char filename[32];
  int amount, i;
  uint8_t zero;
  zero = 0;
  sprintf(filename, "%s/save.aps", game_name);
  entry = SD.open(filename, FILE_WRITE);
  entry.seek(0);
  for(i = 0; i < 10; i++)
    entry.write(zero);
  entry.close();
  sprintf(filename, "%s/map", game_name);
  amount = get_file_amount(filename, ONLY_FILE);
  for(i = 1; i <= amount; i++)
  {
    sprintf(filename, "%s/map/%d.map", game_name, i);
    entry = SD.open(filename, FILE_WRITE);
    entry.seek(0);
    entry.write(zero);
    entry.close();
  }
  show_game_save();
}
void clear_cancel()
{
  work = GAME_SAVE;
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(10, 136, 139, 155);
}
void update_play(unsigned short all, unsigned short win, unsigned lose)
{
  char savename[32];
  unsigned short play_count, win_count, lose_count;
  unsigned char temp[6];
  int i;
  File entry;
  sprintf(savename, "%s/%s", game_name, "save.aps");
  entry = SD.open(savename, FILE_WRITE);
  entry.seek(0);
  for(i = 0; i < 6; i++)
    temp[i] = entry.read();
  play_count = *((unsigned short*)(&temp[0]));
  win_count = *((unsigned short*)(&temp[2]));
  lose_count = *((unsigned short*)(&temp[4]));
  play_count += all;
  win_count += win;
  lose_count += lose;
  entry.seek(0);
  entry.write((uint8_t*)(&play_count), 2);
  entry.write((uint8_t*)(&win_count), 2);
  entry.write((uint8_t*)(&lose_count), 2);
  entry.close();
}
void update_time(uint32_t playtime)
{
  char savename[32];
  uint32_t play_time;
  unsigned char temp[4];
  int i;
  File entry;
  sprintf(savename, "%s/%s", game_name, "save.aps");
  entry = SD.open(savename, FILE_WRITE);
  entry.seek(6);
  for(i = 0; i < 4; i++)
    temp[i] = entry.read();
  play_time = *((uint32_t*)temp);
  play_time += playtime;
  entry.seek(6);
  entry.write((uint8_t*)(&play_time), 4);
  entry.close();
}
void update_map(int index)
{
  char mapname[32];
  uint8_t flag;
  File entry;
  sprintf(mapname, "%s/map/%d.map", game_name, index);
  flag = 1;
  entry = SD.open(mapname, FILE_WRITE);
  entry.seek(0);
  entry.write(flag);
  entry.close();
}

