#include "common.h"
#include "book.h"
#include "main_menu.h"
#include "book_menu.h"
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
      if(myTXT.position() >= txt_max_offset)
        break;
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
void into_book(char* txtname, uint32_t offset)
{
  File myTXT;
  txtbr = txtbg = txtbb = 255;
  txtfr = txtfg = txtfb = 0;
  txtdot = 1;
  if(!file_test(txtname))
    return;
  myTXT = SD.open(txtname);
  txt_max_offset = myTXT.size();
  myTXT.close();
  work = BOOK_SHOW;
  myGLCD.fillScr(txtbr, txtbg, txtbb);
  txt_now_offset = offset;
  txt_next_offset = read_txt(txtname, offset, txtfr, txtfg, txtfb, txtdot);
}
void next_book(char* txtname)
{
  if(txt_next_offset >= txt_max_offset)
    return;
  myGLCD.fillScr(txtbr, txtbg, txtbb);
  txt_now_offset = txt_next_offset;
  txt_next_offset = read_txt(txtname, txt_next_offset, txtfr, txtfg, txtfb, txtdot);
}
void last_book(char* txtname)
{
  
}
uint32_t find_last_offset(char* txtname)
{
  uint32_t temp_offset;
}
void exit_book()
{
  into_book_menu();
  return;
}

