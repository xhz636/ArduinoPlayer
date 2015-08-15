#include "common.h"
#include "book.h"
#include "main_menu.h"
void show_ascii(int x, int y, char c, int r, int g, int b, int dot)
{
  uint32_t offset;
  int i, j;
  byte eight_dots;
  offset = (uint32_t)((c & 0xFF) * 16);
  ASCII.seek(offset);
  myGLCD.setColor(r, g, b);
  for(i = 0; i < 16; i++)
  {
    eight_dots = ASCII.read();
    for(j = 0; j < 8; j++)
      if(eight_dots & 1 << (7 - j))
        if(dot == 1)
          myGLCD.drawPixel(x + j, y + i);
        else
          myGLCD.fillRect(x + j * dot, y + i * dot, x + (j + 1) * dot - 1, y + (i + 1) * dot - 1);
  }
  return;
}
void show_chinese(int x, int y, char* s, int r, int g, int b, int dot)
{
  uint32_t offset;
  int i, j;
  word sixteen_dots;
  offset = (uint32_t)(((s[0] & 0xFF) - 0xA1) * 94 + ((s[1] & 0xFF) - 0xA1)) * 0x20;
  HZK.seek(offset);
  myGLCD.setColor(r, g, b);
  for(i = 0; i < 16; i++)
  {
    sixteen_dots = HZK.read() << 8;
    sixteen_dots = sixteen_dots | HZK.read();
    for(j = 0; j < 16; j++)
      if(sixteen_dots & 1 << (15 - j))
        if(dot == 1)
          myGLCD.drawPixel(x + j, y + i);
        else
          myGLCD.fillRect(x + j * dot, y + i * dot, x + (j + 1) * dot - 1, y + (i + 1) * dot - 1);
  }
  return;
}
uint32_t read_txt(char* txtname, int offset, int r, int g, int b, int dot)
{
  File myTXT;
  uint32_t len, leave = 0;
  int i, j, x_num, y_num;
  char s[3];
  if(!file_test(txtname))
    return 0;
  myTXT = SD.open(txtname);
  myTXT.seek(offset);
  x_num = 220 / (8 * dot);
  y_num = 176 / (16 * dot);
  for(i = 0; i < y_num; i++)
    for(j = 0; j < x_num; j++)
    {
      s[0] = myTXT.read();
      if((s[0] & 0xFF) < 0x80)
      {
        if(s[0] == 0x0D)
        {
          s[1] = myTXT.read();
          break;
        }
        show_ascii(j * 8 * dot, i * 16 * dot, s[0], r, g, b, dot);
      }
      else
      {
        s[1] = myTXT.read();
        s[2] = 0;
        if(j < x_num - 1 || i < y_num - 1)
        {
          if(j >= x_num - 1)
          {
            i++;
            j = 0;
          }
          show_chinese(j * 8 * dot, i * 16 * dot, s, r, g, b, dot);
          leave = 0;
          j++;
        }
        else
          leave = 2;
      }
    }
  len = myTXT.position() - leave;
  myTXT.close();
  return len;
}
void into_book()
{
  work = BOOK_SHOW;
  txt_last_offset = txt_now_offset = 0;
  myGLCD.fillScr(255, 255, 255);
  txt_next_offset = read_txt("zdyjh.txt", txt_now_offset, 0, 0, 0, 1);
}
void next_book()
{
  myGLCD.fillScr(255, 255, 255);
  txt_last_offset = txt_now_offset;
  txt_now_offset = txt_next_offset;
  txt_next_offset = read_txt("zdyjh.txt", txt_now_offset, 0, 0, 0, 1);
}
void last_book()
{
  
}
void exit_book()
{
  show_main_menu();
  return;
}

