#include "common.h"
bool file_test(char* filename)
{
  File test;
  test = SD.open(filename, FILE_WRITE);
  if(test)
  {
    test.close();
    return true;
  }
  else
    return false;
}
int get_file_amount(char* dirname)
{
  int amount = 0;
  File dir, entry;
  dir = SD.open(dirname);
  while(true)
  {
    entry = dir.openNextFile();
    if(entry)
    {
      amount++;
      entry.close();
    }
    else
      break;
  }
  dir.close();
  return amount;
}
void read_file_list(char* dirname, int offset)
{
  int i;
  File dir, entry;
  dir = SD.open(dirname);
  for(i = 0; i < 9; i++)
  {
    entry = dir.openNextFile();
    if(offset)
    {
      entry.close();
      offset--;
      i--;
    }
    else
    {
      if(!entry)
        file_list[i][0] = '\0';
      else
      {
        strcpy(file_list[i], entry.name());
        entry.close();
      }
    }
  }
  dir.close();
}
void show_file_menu()
{
  int i;
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(111, 4, 206, 174);
  for(i = 0; i < 9; i++)
    show_english(111, 4 + 19 * i, file_list[i], 0, 0, 0, 1);
}
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
void show_english(int x, int y, char* sentence, int r, int g, int b, int dot)
{
  int i;
  for(i = 0; i < strlen(sentence); i++)
    show_ascii(x + 8 * i, y, sentence[i], r, g, b, dot);
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
void show_chinese_sentence(int x, int y, char* sentence, int r, int g, int b, int dot)
{
  int i, chinese_count;
  chinese_count = strlen(sentence) / 2;
  for(i = 0; i < chinese_count; i++)
    show_chinese(x + 16 * i, y, sentence + 2 * i, r, g, b, dot);
  return;
}
void change_file_list_point(int change)
{
  if(file_list_point == 0 && change == -1)
  {
    if(file_offset != 0)
    {
      draw_file_list_point(file_list_point, 255, 255, 255);
      file_offset -= 9;
      read_file_list("txt", file_offset);
      show_file_menu();
      file_list_point = 8;
      draw_file_list_point(file_list_point, 255, 0, 0);
    }
  }
  else if(file_list_point == 8 && change == 1)
  {
    if(file_offset + 9 < file_amount)
    {
      draw_file_list_point(file_list_point, 255, 255, 255);
      file_offset += 9;
      read_file_list("txt", file_offset);
      show_file_menu();
      file_list_point = 0;
      draw_file_list_point(file_list_point, 255, 0, 0);
    }
  }
  else if(file_list_point + change < file_amount - file_offset)
  {
    draw_file_list_point(file_list_point, 255, 255, 255);
    file_list_point += change;
    draw_file_list_point(file_list_point, 255, 0, 0);
  }
  return;
}
void draw_file_list_point(int point, int r, int g, int b)
{
  myGLCD.setColor(r, g, b);
  myGLCD.drawRect(109, 2 + 19 * point, 208, 21 + 19 * point);
  switch(work)
  {
    case BOOK_MENU:print_message(point, 10, 99, g, g, b, 1); break;
  }
  return;
}
void print_message(int point, int x, int y, int r, int g, int b, int dot)
{
  switch(work)
  {
    case BOOK_MENU:print_size(point, x, y, r, g, b, dot); break;
  }
}
void print_size(int point, int x, int y, int r, int g, int b, int dot)
{
  char msg[10];
  char unit[4][3] = {"B", "KB", "MB", "GB"};
  char txtname[32];
  int unit_index = 0, size_temp;
  File myTXT;
  switch(work)
  {
    case BOOK_MENU: strcpy(txtname, "txt/"); break;
  }
  strcat(txtname, file_list[file_list_point]);
  if(!file_test(txtname))
    return;
  myTXT = SD.open(txtname);
  size_temp = myTXT.size();
  while(size_temp > 9999)
  {
    size_temp /= 1024;
    unit_index++;
  }
  myTXT.close();
  sprintf(msg, ":%d%s", size_temp, unit[unit_index]);
  show_chinese_sentence(x, y, "\xB4\xF3\xD0\xA1", r, g, b, dot);//大小
  show_english(x + 32, y, msg, r, g, b, dot);
  return;
}

