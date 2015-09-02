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
int get_file_amount(char* dirname, int showdir)
{
  int amount = 0;
  File dir, entry;
  dir = SD.open(dirname);
  dir.rewindDirectory();
  while(true)
  {
    entry = dir.openNextFile();  //打开所有文件，计算数量
    if(entry)
    {
      switch(showdir)
      {
        case ONLY_FILE: if(!entry.isDirectory()) amount++; break;  //只显示文件
        case ONLY_DIR: if(entry.isDirectory()) amount++; break;  //只显示目录
        case BOTH_FILE_DIR: amount++; break;
      }
      entry.close();
    }
    else
      break;
  }
  dir.close();
  return amount;
}
void read_file_list(char* dirname, int offset, int showdir)
{
  int i;
  File dir, entry;
  dir = SD.open(dirname);
  dir.rewindDirectory();
  for(i = 0; i < 9; i++)
  {
    entry = dir.openNextFile();
    if(offset)  //跳过偏移前文件
    {
      switch(showdir)
      {
        case ONLY_FILE: if(!entry.isDirectory())
                {
                  offset--;
                  i--;
                }
                break;
        case ONLY_DIR: if(entry.isDirectory())
                {
                  offset--;
                  i--;
                }
                break;
        case BOTH_FILE_DIR: offset--;
                i--;
                break;
      }
      entry.close();
    }
    else
    {
      file_list[i][0] = '\0';
      if(entry)
      {
        //保存文件名
        switch(showdir)
        {
          case ONLY_FILE: if(!entry.isDirectory())
                    strcpy(file_list[i], entry.name());
                  else
                    i--;
                  break;  //只显示文件
          case ONLY_DIR: if(entry.isDirectory())
                    strcpy(file_list[i], entry.name());
                  else
                    i--;
                  break;  //只显示目录
          case BOTH_FILE_DIR: strcpy(file_list[i], entry.name()); break;
        }
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
  offset = (uint32_t)((c & 0xFF) * 16);  //计算对应字库中的偏移
  ASCII.seek(offset);
  myGLCD.setColor(r, g, b);
  for(i = 0; i < 16; i++)
  {
    eight_dots = ASCII.read();
    for(j = 0; j < 8; j++)  //逐行描点
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
  offset = (uint32_t)(((s[0] & 0xFF) - 0xA1) * 94 + ((s[1] & 0xFF) - 0xA1)) * 0x20;  //计算对应字库中的偏移
  HZK.seek(offset);
  myGLCD.setColor(r, g, b);
  for(i = 0; i < 16; i++)
  {
    sixteen_dots = HZK.read() << 8;
    sixteen_dots = sixteen_dots | HZK.read();  //2个字符组成一个汉字
    for(j = 0; j < 16; j++)  //逐行描点
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
  if(file_list_point == 0 && change == -1)  //上一页文件列表
  {
    if(file_offset != 0)
    {
      draw_file_list_point(file_list_point, 255, 255, 255);
      file_offset -= 9;
      read_file_list(workdirname, file_offset, workdircase);
      show_file_menu();
      file_list_point = 8;
      draw_file_list_point(file_list_point, 255, 0, 0);
    }
  }
  else if(file_list_point == 8 && change == 1)  //下一页文件列表
  {
    if(file_offset + 9 < file_amount)
    {
      draw_file_list_point(file_list_point, 255, 255, 255);
      file_offset += 9;
      read_file_list(workdirname, file_offset, workdircase);
      show_file_menu();
      file_list_point = 0;
      draw_file_list_point(file_list_point, 255, 0, 0);
    }
  }
  else if(change == -9)
  {
    if(file_offset - 9 >= 0)
    {
      draw_file_list_point(file_list_point, 255, 255, 255);
      file_offset -= 9;
      read_file_list(workdirname, file_offset, workdircase);
      show_file_menu();
      draw_file_list_point(file_list_point, 255, 0, 0);
    }
  }
  else if(change == 9)
  {
    if(file_offset + 9 < file_amount)
    {
      draw_file_list_point(file_list_point, 255, 255, 255);
      file_offset += 9;
      read_file_list(workdirname, file_offset, workdircase);
      show_file_menu();
      if(file_list_point >= file_amount - file_offset)
        file_list_point = file_amount - file_offset - 1;
      draw_file_list_point(file_list_point, 255, 0, 0);
    }
  }
  else if(file_list_point + change < file_amount - file_offset)  //当前页内移动光标
  {
    draw_file_list_point(file_list_point, 255, 255, 255);
    file_list_point += change;
    draw_file_list_point(file_list_point, 255, 0, 0);
  }
  return;
}
void draw_file_list_point(int point, int r, int g, int b)
{
  char filename[32];
  myGLCD.setColor(r, g, b);
  myGLCD.drawRect(109, 2 + 19 * point, 208, 21 + 19 * point);
  switch(work)
  {
    case BOOK_MENU: {
                      sprintf(filename, "book/%s", file_list[point]);
                      print_message(filename, 10, 99, g, g, b, 1);
                      break;
                    }
    case MUSIC_MENU:{
                      strcpy(filename, file_list[point]);
                      print_message(filename, 10, 115, g, g, b, 1);
                      break;
                    }
    case IMAGE_MENU: {
                       sprintf(filename, "image/%s", file_list[point]);
                       print_message(filename, 10, 99, g, g, b, 1);
                       break;
                     }
  }
  return;
}
void print_message(char* filename, int x, int y, int r, int g, int b, int dot)
{
  switch(work)
  {
    case BOOK_MENU:print_size(filename, x, y, r, g, b, dot); break;
    case MUSIC_MENU:print_size(filename, x, y, r, g, b, dot);
                    print_music_long(filename, x, y + 16, r, g, b, dot);
                    break;
    case IMAGE_MENU:print_size(filename, x, y, r, g, b, dot);
                    print_image_size(filename, x, y + 16, r, g, b, dot);
                    break;
  }
}
void print_size(char* filename, int x, int y, int r, int g, int b, int dot)
{
  char msg[10];
  char unit[4][3] = {"B", "KB", "MB", "GB"};
  int unit_index = 0;
  uint32_t size_temp;
  File entry;
  if(!file_test(filename))
    return;
  entry = SD.open(filename);
  size_temp = entry.size();  //读取文件大小
  while(size_temp > 9999)  //超过4位转换单位
  {
    size_temp /= 1024;
    unit_index++;
  }
  entry.close();
  sprintf(msg, ":%d%s", (int)size_temp, unit[unit_index]);
  show_chinese_sentence(x, y, "\xB4\xF3\xD0\xA1", r, g, b, dot);//大小
  show_english(x + 32, y, msg, r, g, b, dot);
  return;
}
void print_music_long(char* filename, int x, int y, int r, int g, int b, int dot)
{
  char msg[10];
  uint32_t size_temp;
  int timelong;
  File entry;
  if(!file_test(filename))
    return;
  entry = SD.open(filename);
  size_temp = entry.size();  //读取文件大小
  entry.close();
  timelong = size_temp / 62500;
  sprintf(msg, ":%02d:%02d", timelong / 60, timelong % 60);
  show_chinese_sentence(x, y, "\xB3\xA4\xB6\xC8", r, g, b, dot);//长度
  show_english(x + 32, y, msg, r, g, b, dot);
  return;
}
void read_image_size(char* imagename)
{
  unsigned char temp[2];
  File entry;
  if(!file_test(imagename))
    return;
  entry = SD.open(imagename);
  temp[0] = entry.read();
  temp[1] = entry.read();
  image_width = *(unsigned short*)temp;  //读取图片宽度
  temp[0] = entry.read();
  temp[1] = entry.read();
  image_height = *(unsigned short*)temp;  //读取图片高度
  entry.close();
}
void print_image_size(char* filename, int x, int y, int r, int g, int b, int dot)
{
  char msg[10];
  read_image_size(filename);
  sprintf(msg, ":%hu", image_width);
  show_chinese_sentence(x, y, "\xBF\xED\xB6\xC8", r, g, b, dot);//宽度
  show_english(x + 32, y, msg, r, g, b, dot);
  sprintf(msg, ":%hu", image_height);
  show_chinese_sentence(x, y + 16, "\xB8\xDF\xB6\xC8", r, g, b, dot);//高度
  show_english(x + 32, y + 16, msg, r, g, b, dot);
  return;
}

