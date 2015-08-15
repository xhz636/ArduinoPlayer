#include "common.h"
#include "main_menu.h"
void show_main_menu()
{
  myGLCD.fillScr(255, 255, 255);
  show_apimg(0, 176 - 30, "sys/bottom.api");
  show_apimg(39 - 31, 39 - 31, "sys/book.api");
  show_apimg(110 - 31, 39 - 31, "sys/music.api");
  show_apimg(181 - 31, 39 - 31, "sys/image.api");
  show_apimg(39 -31, 110 - 31, "sys/game.api");
  show_apimg(110 - 31, 110 - 31, "sys/file.api");
  show_apimg(181 - 31, 110 - 31, "sys/set.api");
  work = MAIN_MENU;
  main_menu_point = 0;
  draw_main_menu_point(main_menu_point, 255, 0, 0);
  return;
}
void show_apimg(int x, int y, char* apimgname)
{
  File apimg;
  unsigned char temp[2];
  unsigned char width, height, i, j;
  unsigned char r, g, b, a;
  if(!file_test(apimgname))
    return;
  apimg = SD.open(apimgname);
  temp[0] = apimg.read();
  temp[1] = apimg.read();
  width = *(unsigned short*)temp;
  temp[0] = apimg.read();
  temp[1] = apimg.read();
  height = *(unsigned short*)temp;
  for(j = 0; j < height; j++)
    for(i = 0; i < width; i++)
    {
      b = apimg.read();
      g = apimg.read();
      r = apimg.read();
      a = apimg.read();
      myGLCD.setColor(r, g, b);
      myGLCD.drawPixel(x + i, y + j);
    }
  apimg.close();
  return;
}
void change_main_menu_point(int change_x, int change_y)
{
  draw_main_menu_point(main_menu_point, 255, 255, 255);
  if(change_x)
    main_menu_point = (main_menu_point / 3) * 3 + (main_menu_point + 3 + change_x) % 3;
  if(change_y)
    main_menu_point = (main_menu_point + 6 + change_y * 3) % 6;
  draw_main_menu_point(main_menu_point, 255, 0, 0);
}
void draw_main_menu_point(int point, int r, int g, int b)
{
  int x, y;
  int table[3] = {39, 110, 181};
  x = table[point % 3];
  y = table[point / 3];
  myGLCD.setColor(r, g, b);
  myGLCD.drawCircle(x, y, 33);
  myGLCD.drawCircle(x, y, 35);
  return;
}
