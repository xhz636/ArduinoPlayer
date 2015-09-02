#include "common.h"
#include "image.h"
#include "menu.h"
void into_image(char* imagename)
{
  work = IMAGE_SHOW;
  image_mode = image_temp_mode = AUTOSIZE;
  image_state = NORMAL;
  image_left_offset = image_top_offset = 0;
  image_temp_left_offset = image_temp_top_offset = 0;
  image_point = 0;
  image_amount = file_amount;
  image_offset = file_offset + file_list_point;
  draw_image_show();
  show_image(image_name, image_mode, image_state, image_left_offset, image_top_offset);
}
void exit_image()
{
  main_menu_point = 2;
  into_menu();
  return;
}
void draw_image_show()
{
  char temp[16];
  myGLCD.fillScr(255, 255, 255);
  clr_image();
  sprintf(temp, ":%hu*%hu", image_width, image_height);
  show_chinese_sentence(2, 0, "\xB4\xF3\xD0\xA1", 0, 0, 0, 1);//大小
  show_english(2 + 32, 0, temp, 0, 0, 0, 1);
  show_chinese_sentence(110, 0, "\xCB\xF5\xB7\xC5\xB1\xC8\xC0\xFD", 0, 0, 0, 1);//缩放比例
  show_ascii(110 + 16 * 4, 0, ':', 0, 0, 0, 1);
  show_image_mode(0, 0, 0);
  show_chinese_sentence(162, 18, "\xCD\xBC", 0, 0, 0, 1);//图
  show_ascii(162 + 16, 18, ':', 0, 0, 0, 1);
  show_image_temp_mode(0, 0, 0);
  show_chinese_sentence(162, 37, "\xD7\xF3", 0, 0, 0, 1);//左
  show_ascii(162 + 16, 37, ':', 0, 0, 0, 1);
  show_image_left(0, 0, 0);
  show_chinese_sentence(162, 56, "\xC9\xCF", 0, 0, 0, 1);//上
  show_ascii(162 + 16, 56, ':', 0, 0, 0, 1);
  show_image_top(0, 0, 0);
  show_chinese_sentence(162, 75, "\xD3\xA6\xD3\xC3", 0, 0, 0, 1);//应用
  show_chinese_sentence(162, 101, "\xC4\xE6\xCA\xB1\xD5\xEB", 0, 0, 0, 1);//逆时针
  show_chinese_sentence(162, 120, "\xCB\xB3\xCA\xB1\xD5\xEB", 0, 0, 0, 1);//顺时针
  show_chinese_sentence(162, 139, "\xC9\xCF\xD2\xBB\xD5\xC5", 0, 0, 0, 1);//上一张
  show_chinese_sentence(162, 158, "\xCF\xC2\xD2\xBB\xD5\xC5", 0, 0, 0, 1);//上一张
  draw_image_point(image_point, 255, 0, 0);
}
void clr_image()
{
  myGLCD.setColor(233, 233, 233);
  myGLCD.fillRect(0, 16, 159, 175);
}
void draw_image_point(int point, int r, int g, int b)
{
  int y1[8] = {16, 35, 54, 73, 99, 118, 137, 156};
  int y2[8] = {35, 54, 73, 92, 118, 137, 156, 175};
  myGLCD.setColor(r, g, b);
  myGLCD.drawRect(160, y1[point], 219, y2[point]);
}
void change_image_point(int change)
{
  if(image_point + change >= 0 && image_point + change < 8)
  {
    draw_image_point(image_point, 255, 255, 255);
    image_point += change;
    draw_image_point(image_point, 255, 0, 0);
    delay(200);
  }
}
void show_image_mode(int r, int g, int b)
{
  switch(image_mode)
  {
    case AUTOSIZE:show_chinese_sentence(110 + 16 * 4 + 8, 0, "\xD7\xD4\xB6\xAF", r, g, b, 1); break;//自动
    case FULLSIZE:show_english(110 + 16 * 4 + 8, 0, "100%", r, g, b, 1); break;
    case HALFSIZE:show_english(110 + 16 * 4 + 8, 0, "50%", r, g, b, 1);  break;
    case QTRSIZE: show_english(110 + 16 * 4 + 8, 0, "25%", r, g, b, 1);  break;
  }
}
void show_image_temp_mode(int r, int g, int b)
{
  switch(image_temp_mode)
  {
    case AUTOSIZE:show_chinese_sentence(162 + 24, 18, "\xD7\xD4\xB6\xAF", r, g, b, 1); break;//自动
    case FULLSIZE:show_english(162 + 24, 18, "100%", r, g, b, 1); break;
    case HALFSIZE:show_english(162 + 24, 18, "50%", r, g, b, 1);  break;
    case QTRSIZE: show_english(162 + 24, 18, "25%", r, g, b, 1);  break;
  }
}
void show_image_left(int r, int g, int b)
{
  char temp[8];
  sprintf(temp, "%d", image_temp_left_offset);
  show_english(162 + 24, 37, temp, r, g, b, 1);
}
void show_image_top(int r, int g, int b)
{
  char temp[8];
  sprintf(temp, "%d", image_temp_top_offset);
  show_english(162 + 24, 56, temp, r, g, b, 1);
}
void change_image_mode(int change)
{
  show_image_temp_mode(255, 255, 255);
  switch(image_temp_mode)
  {
    case AUTOSIZE:if(change > 0)
                    image_temp_mode = FULLSIZE;
                  else
                    image_temp_mode = QTRSIZE;
                  break;
    case FULLSIZE:if(change > 0)
                    image_temp_mode = HALFSIZE;
                  else
                    image_temp_mode = AUTOSIZE;
                  break;
    case HALFSIZE:if(change > 0)
                    image_temp_mode = QTRSIZE;
                  else
                    image_temp_mode = FULLSIZE;
                  break;
    case QTRSIZE: if(change > 0)
                    image_temp_mode = AUTOSIZE;
                  else
                    image_temp_mode = HALFSIZE;
                  break;
  }
  show_image_temp_mode(0, 0, 0);
}
void change_image_left(int change)
{
  if(image_temp_left_offset + change >= 0 && image_temp_left_offset + change < 1024 - 160)
  {
    show_image_left(255, 255, 255);
    image_temp_left_offset += change;
    show_image_left(0, 0, 0);
  }
}
void change_image_top(int change)
{
  if(image_temp_top_offset + change >= 0 && image_temp_top_offset + change < 768 - 160)
  {
    show_image_top(255, 255, 255);
    image_temp_top_offset += change;
    show_image_top(0, 0, 0);
  }
}
void image_update()
{
  image_mode = image_temp_mode;
  image_left_offset = image_temp_left_offset;
  image_top_offset = image_temp_top_offset;
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRect(110 + 16 * 4 + 8, 0, 219, 15);
  show_image_mode(0, 0, 0);
  clr_image();
  show_image(image_name, image_mode, image_state, image_left_offset, image_top_offset);
}
void image_left_spin()
{
  switch(image_state)
  {
    case NORMAL: image_state = LEFTSPIN; break;
    case LEFTSPIN: image_state = SEMISPIN; break;
    case RIGHTSPIN: image_state = NORMAL; break;
    case SEMISPIN: image_state = RIGHTSPIN; break;
  }
  clr_image();
  show_image(image_name, image_mode, image_state, image_left_offset, image_top_offset);
}
void image_right_spin()
{
  switch(image_state)
  {
    case NORMAL: image_state = RIGHTSPIN; break;
    case LEFTSPIN: image_state = NORMAL; break;
    case RIGHTSPIN: image_state = SEMISPIN; break;
    case SEMISPIN: image_state = LEFTSPIN; break;
  }
  clr_image();
  show_image(image_name, image_mode, image_state, image_left_offset, image_top_offset);
}
void find_image(int amount, int offset)
{
  File dir, entry;
  dir = SD.open("image");
  dir.rewindDirectory();
  while(1)
  {
    entry = dir.openNextFile();
    if(offset)  //跳过偏移前文件
    {
      if(!entry.isDirectory())
        offset--;
      entry.close();
    }
    else if(entry)
    {
      if(!entry.isDirectory())
      {
        sprintf(image_name, "image/%s", entry.name());
        break;
      }
      entry.close();
    }
  }
  dir.close();
}
void clr_msg()
{
  draw_image_point(image_point, 255, 255, 255);
  myGLCD.fillRect(2 + 32 + 8, 0, 109, 15);
  myGLCD.fillRect(110 + 16 * 4 + 8, 0, 219, 15);
  myGLCD.fillRect(162 + 24, 18, 217, 71);
}
void image_next(int change)
{
  char temp[8];
  if(image_offset + change >= 0 && image_offset + change < image_amount)
    image_offset += change;
  else
    return;
  find_image(image_amount, image_offset);
  clr_msg();
  read_image_size(image_name);
  image_mode = image_temp_mode = AUTOSIZE;
  image_state = NORMAL;
  image_left_offset = image_top_offset = 0;
  image_temp_left_offset = image_temp_top_offset = 0;
  image_point = 0;
  sprintf(temp, "%hu*%hu", image_width, image_height);
  show_english(2 + 32 + 8, 0, temp, 0, 0, 0, 1);
  show_image_mode(0, 0, 0);
  show_image_temp_mode(0, 0, 0);
  show_image_left(0, 0, 0);
  show_image_top(0, 0, 0);
  draw_image_point(image_point, 255, 0, 0);
  clr_image();
  show_image(image_name, image_mode, image_state, image_left_offset, image_top_offset);
}
void show_image(char* imagename, int mode, int state, int left, int top)
{
  File apimg;
  int i, j;
  int left_start, top_start;
  int width_insample, height_insample;
  unsigned char r, g, b, a;
  if(!file_test(imagename))
    return;
  mode2sample(mode, state);
  if(image_width_insample < 160)
  {
    left_start = (160 - image_width_insample) / 2;
    width_insample = image_width_insample;
  }
  else
  {
    left_start = 0;
    width_insample = 160;
  }
  if(image_height_insample < 160)
  {
    top_start = (160 - image_height_insample) / 2 + 16;
    height_insample = image_height_insample;
  }
  else
  {
    top_start = 16;
    height_insample = 160;
  }
  if(image_width_insample <= 160)
  {
    if(left > 0)
    {
      image_left_offset = left = 0;
      show_image_left(255, 255, 255);
      image_temp_left_offset = image_left_offset;
      show_image_left(0, 0, 0);
    }
  }
  else if(left + 160 > image_width_insample)
  {
    image_left_offset = left = image_width_insample - 160;
    show_image_left(255, 255, 255);
    image_temp_left_offset = image_left_offset;
    show_image_left(0, 0, 0);
  }
  if(image_height_insample <= 160)
  {
    if(top > 0)
    {
      image_top_offset = top = 0;
      show_image_top(255, 255, 255);
      image_temp_top_offset = image_top_offset;
      show_image_top(0, 0, 0);
    }
  }
  else if(top + 160 > image_height_insample)
  {
    image_top_offset = top = image_height_insample - 160;
    show_image_top(255, 255, 255);
    image_temp_top_offset = image_top_offset;
    show_image_top(0, 0, 0);
  }
  apimg = SD.open(imagename);
  for(j = 0; j < height_insample; j++)  //逐行描点
    for(i = 0; i < width_insample; i++)
    {
      apimg.seek(find_image_offset(i, j, state, left, top, width_insample, height_insample));
      b = apimg.read();
      g = apimg.read();
      r = apimg.read();
      a = apimg.read();
      myGLCD.setColor(r, g, b);
      myGLCD.drawPixel(left_start + i, top_start + j);
      if(digitalRead(btnSTART) == LOW)
      {
        apimg.close();
        return;
      }
    }
  apimg.close();
  return;
}
void mode2sample(int mode, int state)
{
  switch(mode)
  {
    case AUTOSIZE:if(image_width <= 160 && image_height <= 160)
                    image_sample = 1.0;
                  else
                    image_sample = (double)image_width / 160.0 > (double)image_height / 160.0 ? (double)image_width / 160.0 : (double)image_height / 160.0;
                  break;
    case FULLSIZE:image_sample = 1.0; break;
    case HALFSIZE:image_sample = 2.0; break;
    case QTRSIZE: image_sample = 4.0; break;
  }
  switch(state)
  {
    case NORMAL: case SEMISPIN:
      image_width_insample = (int)((double)image_width / image_sample);
      image_height_insample = (int)((double)image_height / image_sample);
      break;
    case LEFTSPIN: case RIGHTSPIN:
      image_height_insample = (int)((double)image_width / image_sample);
      image_width_insample = (int)((double)image_height / image_sample);
      break;
  }
}
uint32_t find_image_offset(int x, int y, int state, int left, int top, int width, int height)
{
  uint32_t offset_point, offset_api;
  int x_t, y_t;
  switch(state)
  {
    case NORMAL: break;
    case LEFTSPIN:{
                    x_t = x;
                    y_t = y;
                    x = height - y_t - 1;
                    y = x_t;
                    break;
                  }
    case RIGHTSPIN: {
                      x_t = x;
                      y_t = y;
                      x = y_t;
                      y = width - x_t - 1;
                      break;
                    }
    case SEMISPIN:{
                    x_t = x;
                    y_t = y;
                    x = width - x_t - 1;
                    y = height - y_t - 1;
                    break;
                  }
  }
  offset_point = (uint32_t)((double)(y + top) * image_sample) * image_width + (uint32_t)((double)(x + left) * image_sample);
  offset_api = offset_point * 4 + 4;
  return offset_api;
}
