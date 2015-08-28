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
void into_book_config()
{
  work = BOOK_CONFIG;
  myGLCD.fillScr(255, 255, 255);
  show_chinese_sentence(10, 26, "\xB1\xB3\xBE\xB0\xD1\xD5\xC9\xAB", 0, 0, 0, 1);//背景颜色
  myGLCD.setColor(txtbr, txtbb, txtbg);
  myGLCD.fillRect(82, 2, 145, 65);
  show_chinese_sentence(10, 92, "\xD7\xD6\xCC\xE5\xD1\xD5\xC9\xAB", 0, 0, 0, 1);//字体颜色
  myGLCD.setColor(txtfr, txtfb, txtfg);
  myGLCD.fillRect(82, 68, 145, 131);
  show_chinese_sentence(10, 136, "\xD7\xD6\xCC\xE5\xB4\xF3\xD0\xA1", 0, 0, 0, 1);//字体大小
  show_chinese_sentence(10, 156, "\xD4\xC4\xB6\xC1\xBD\xF8\xB6\xC8", 0, 0, 0, 1);//阅读进度
  show_chinese_sentence(178, 136, "\xC8\xB7\xB6\xA8", 0, 0, 0, 1);//确定
  show_chinese_sentence(178, 156, "\xC8\xA1\xCF\xFB", 0, 0, 0, 1);//取消
}
void exit_book_config()
{
  work = BOOK_SHOW;
  txt_next_offset = txt_now_offset;
  next_book(book_name);
}

