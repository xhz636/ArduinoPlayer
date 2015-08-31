#include "common.h"
#include "music.h"
#include "menu.h"
int freeRam ()
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
void into_music(char* musicname)
{
  if(!music_success)
    return;
  if(!SdPlay.setFile(musicname))
    return;
  work = MUSIC_PLAY;
  myGLCD.fillScr(255, 255, 255);
  SdPlay.play();
}
void exit_music()
{
  SdPlay.stop();
  main_menu_point = 1;
  into_menu();
  return;
}

