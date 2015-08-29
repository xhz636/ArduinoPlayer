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
  char temp[4];
  work = BOOK_CONFIG;
  book_config_point = 0;
  temp_r[0] = txtbr;
  temp_g[0] = txtbg;
  temp_b[0] = txtbb;
  temp_r[1] = txtfr;
  temp_g[1] = txtfg;
  temp_b[1] = txtfb;
  temp_dot = txtdot;
  temp_offset_rate = txt_now_offset * 100 / txt_max_offset;
  myGLCD.fillScr(255, 255, 255);
  show_chinese_sentence(10, 26, "\xB1\xB3\xBE\xB0\xD1\xD5\xC9\xAB", 0, 0, 0, 1);//背景颜色
  myGLCD.setColor(txtbr, txtbg, txtbb);
  myGLCD.fillRect(82, 2, 145, 65);
  show_chinese_sentence(10, 92, "\xD7\xD6\xCC\xE5\xD1\xD5\xC9\xAB", 0, 0, 0, 1);//字体颜色
  myGLCD.setColor(txtfr, txtfg, txtfb);
  myGLCD.fillRect(82, 68, 145, 131);
  show_chinese_sentence(10, 136, "\xD7\xD6\xCC\xE5\xB4\xF3\xD0\xA1", 0, 0, 0, 1);//字体大小
  sprintf(temp, "%d", txtdot);
  show_english(82, 136, temp, 0, 0, 0, 1);
  show_chinese_sentence(10, 156, "\xD4\xC4\xB6\xC1\xBD\xF8\xB6\xC8", 0, 0, 0, 1);//阅读进度
  sprintf(temp, "%d", temp_offset_rate);
  show_english(82, 156, temp, 0, 0, 0, 1);
  show_chinese_sentence(178, 136, "\xC8\xB7\xB6\xA8", 0, 0, 0, 1);//确定
  show_chinese_sentence(178, 156, "\xC8\xA1\xCF\xFB", 0, 0, 0, 1);//取消
  draw_book_config_point(book_config_point, 255, 0, 0);
}
void draw_book_config_point(int point, int r, int g, int b)
{
  int x1[6] = {8, 8, 8, 8, 176, 176};
  int y1[6] = {24, 90, 134, 154, 134, 154};
  int x2[6] = {75, 75, 75, 75, 211, 211};
  int y2[6] = {43, 109, 153, 173, 153, 173};
  myGLCD.setColor(r, g, b);
  myGLCD.drawRect(x1[point], y1[point], x2[point], y2[point]);
}
void change_book_config_point()
{
  draw_book_config_point(book_config_point, 255, 255, 255);
  book_config_point++;
  book_config_point %= 6;
  draw_book_config_point(book_config_point, 255, 0, 0);
}
void show_pallet(int point)
{
  char temp[8];
  temp_point = 0;
  in_pallet = true;
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(146, 2 + 66 * book_config_point, 209, 2 + 66 * book_config_point + 63);
  show_chinese(146, 2 + 66 * point, "\xA1\xFA", 255, 0, 0, 1);
  sprintf(temp, "R %d", temp_r[point]);
  show_english(146 + 16, 2 + 66 * point, temp, 0, 0, 0, 1);
  sprintf(temp, "G %d", temp_g[point]);
  show_english(146 + 16, 2 + 66 * point + 16, temp, 0, 0, 0, 1);
  sprintf(temp, "B %d", temp_b[point]);
  show_english(146 + 16, 2 + 66 * point + 32, temp, 0, 0, 0, 1);
  show_chinese_sentence(146 + 16, 2 + 66 * point + 48, "\xD4\xA4\xC0\xC0", 0, 0, 0, 1);//预览
}
void change_temp_rgb(int rgb, int point, int change)
{
  char temp[4];
  int temp_rgb;
  switch(rgb)
  {
    case 0: temp_rgb = temp_r[point]; break;
    case 1: temp_rgb = temp_g[point]; break;
    case 2: temp_rgb = temp_b[point]; break;
  }
  if(temp_rgb + change < 256 && temp_rgb + change >= 0)
  {
    sprintf(temp, "%d", temp_rgb);
    show_english(146 + 32, 2 + 66 * point + 16 * rgb, temp, 255, 255, 255, 1);
    temp_rgb += change;
    sprintf(temp, "%d", temp_rgb);
    show_english(146 + 32, 2 + 66 * point + 16 * rgb, temp, 0, 0, 0, 1);
  }
  switch(rgb)
  {
    case 0: temp_r[point] = temp_rgb; break;
    case 1: temp_g[point] = temp_rgb; break;
    case 2: temp_b[point] = temp_rgb; break;
  }
}
void change_pallet_point(int change)
{
  show_chinese(146, 2 + 66 * book_config_point + 16 * temp_point, "\xA1\xFA", 255, 255, 255, 1);
  temp_point += change;
  if(temp_point < 0)
    temp_point = 3;
  temp_point %= 4;
  show_chinese(146, 2 + 66 * book_config_point + 16 * temp_point, "\xA1\xFA", 255, 0, 0, 1);
}
void change_dot(int change)
{
  if(temp_dot + change > 0 && temp_dot + change < 6)
  {
    show_ascii(82, 136, temp_dot + '0', 255, 255, 255, 1);
    temp_dot += change;
    show_ascii(82, 136, temp_dot + '0', 0, 0, 0, 1);
  }
}
void change_offset(int change)
{
  char temp[4];
  if(temp_offset_rate + change <= 100 && temp_offset_rate + change >= 0)
  {
    sprintf(temp, "%d", temp_offset_rate);
    show_english(82, 156, temp, 255, 255, 255, 1);
    temp_offset_rate += change;
    sprintf(temp, "%d", temp_offset_rate);
    show_english(82, 156, temp, 0, 0, 0, 1);
  }
}
void exit_book_config()
{
  work = BOOK_SHOW;
  txt_next_offset = txt_now_offset;
  next_book(book_name);
}

