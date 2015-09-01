#include "common.h"
#include "music.h"
#include "menu.h"
int freeRam ()
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
void show_freeram()
{
  char rammsg[16];
  sprintf(rammsg, "RAM:%dB", freeRam());
  show_english(10, 99 + 3 * 16, rammsg, 0, 0, 0, 1);
}
void into_music(char* musicname)
{
  if(!music_success)
    return;
  if(!SdPlay.setFile(musicname))
    return;
  work = MUSIC_PLAY;
  music_state = ISPLAY;
  music_mode = ORDER;
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(109, 0, 219, 175);
  show_english(10, 99, musicname, 0, 0, 0, 1);
  show_freeram();
  draw_music_play();
  SdPlay.play();
}
void exit_music()
{
  SdPlay.stop();
  main_menu_point = 1;
  into_menu();
  return;
}
void draw_music_play()
{
  show_music_state();
  show_music_mode();
  show_music_help();
}
void show_music_state()
{
  show_chinese_sentence(111, 4 + 19 * 0, "\xD7\xB4\xCC\xAC", 0, 0, 0, 1);//状态
  draw_music_state(0, 0, 0);
}
void draw_music_state(int r, int g, int b)
{
  if(r == 0 && g == 0 && b == 0)
    switch(music_state)
    {
      case ISPLAY: g = 255; break;
      case ISPAUSE: b = 255; break;
      case ISSTOP: r = 255; break;
    }
  myGLCD.setColor(r, g, b);
  switch(music_state)
  {
    case ISPLAY: myGLCD.drawLine(150, 4, 150, 19);
                 myGLCD.drawLine(150, 4, 157, 11);
                 myGLCD.drawLine(150, 19, 157, 12);
                 break;
    case ISPAUSE:myGLCD.drawLine(150, 4, 150, 19);
                 myGLCD.drawLine(151, 4, 151, 19);
                 myGLCD.drawLine(157, 4, 157, 19);
                 myGLCD.drawLine(158, 4, 158, 19);
                 break;
    case ISSTOP: myGLCD.fillRect(150, 4, 165, 19);
                 break;
  }
}
void show_music_mode()
{
  show_chinese_sentence(111, 4 + 19 * 1, "\xB5\xA5\xC7\xFA\xD1\xAD\xBB\xB7", 0, 0, 0, 1);//单曲循环
  show_chinese_sentence(111, 4 + 19 * 2, "\xCB\xB3\xD0\xF2\xB2\xA5\xB7\xC5", 0, 0, 0, 1);//顺序播放
  show_chinese_sentence(111, 4 + 19 * 3, "\xCB\xE6\xBB\xFA\xB2\xA5\xB7\xC5", 0, 0, 0, 1);//随机播放
  draw_music_mode(255, 0, 0);
}
void draw_music_mode(int r, int g, int b)
{
  myGLCD.setColor(r, g, b);
  switch(music_mode)
  {
    case SINGLE:myGLCD.drawRect(109, 2 + 19 * 1, 176, 21 + 19 * 1); break;
    case ORDER: myGLCD.drawRect(109, 2 + 19 * 2, 176, 21 + 19 * 2); break;
    case RANDOM:myGLCD.drawRect(109, 2 + 19 * 3, 176, 21 + 19 * 3); break;
  }
}
void show_music_help()
{
  show_chinese_sentence(111, 4 + 19 * 4, "\xB0\xEF\xD6\xFA\xA3\xBA", 0, 0, 0, 1);//帮助：
  show_english(111, 4 + 19 * 5, "LEFT:", 0, 0, 0, 1);
  show_chinese_sentence(111 + 8 * 5, 4 + 19 * 5, "\xC9\xCF\xD2\xBB\xC7\xFA", 0, 0, 0, 1);//上一曲
  show_english(111, 4 + 19 * 6, "RIGHT:", 0, 0, 0, 1);
  show_chinese_sentence(111 + 8 * 6, 4 + 19 * 6, "\xCF\xC2\xD2\xBB\xC7\xFA", 0, 0, 0, 1);//下一曲
  show_english(111, 4 + 19 * 7, "START:", 0, 0, 0, 1);
  show_chinese_sentence(111 + 8 * 6, 4 + 19 * 7, "\xD4\xDD\xCD\xA3", 0, 0, 0, 1);//暂停
  show_english(111, 4 + 19 * 8, "SELECT:", 0, 0, 0, 1);
  show_chinese_sentence(111 + 8 * 7, 4 + 19 * 8, "\xC4\xA3\xCA\xBD", 0, 0, 0, 1);//模式
}
void change_music_state()
{
  draw_music_state(255, 255, 255);
  SdPlay.pause();
  if(SdPlay.isPlaying())
    music_state = ISPLAY;
  else if(SdPlay.isPaused())
    music_state = ISPAUSE;
  draw_music_state(0, 0, 0);
}
void change_music_mode()
{
  draw_music_mode(255, 255, 255);
  switch(music_mode)
  {
    case SINGLE:music_mode = ORDER; break;
    case ORDER: music_mode = RANDOM; break;
    case RANDOM:music_mode = SINGLE; break;
  }
  draw_music_mode(255, 0, 0);
}

