#include <UTFT.h>
#include <SPI.h>
#include <SD.h>
UTFT myGLCD(QD220A, A2, A1, A5, A4, A3);
File HZK, ASCII;
bool file_test(char* filename);
void read_hz();
void show_ascii(int x, int y, char c, int r, int g, int b, int dot);
void show_chinese(int x, int y, char* s, int r, int g, int b, int dot);
uint32_t read_txt(char* txtname, int offset, int r, int g, int b, int dot);
void show_apimg(int x, int y, char* apimgname);
void setup()
{
  uint32_t txtp;
  int i;
  randomSeed(analogRead(0));
  myGLCD.InitLCD();
  myGLCD.InitLCD();//Initializes twice to improve reliability
  if(!SD.begin(4))
  {
    myGLCD.fillScr(255, 0, 0);
    return;
  }
  read_hz();
  show_apimg(0, 0, "sys/main.api");
  myGLCD.fillScr(255, 255, 255);
  show_apimg(0, 176 - 30, "sys/bottom.api");
  show_apimg(8, 8, "sys/book.api");
  show_apimg(78, 8, "sys/music.api");
  show_apimg(148, 8, "sys/image.api");
  show_apimg(8, 78, "sys/game.api");
  show_apimg(78, 78, "sys/file.api");
  show_apimg(148, 78, "sys/set.api");
  for(i = 0, txtp = 0; i < 100; i++)
  {
    myGLCD.fillScr(255, 255, 255);
    txtp = read_txt("zdyjh.txt", txtp, 0, 0, 0, 1);
  }
  HZK.close();
}
void loop()
{
  
}
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
void read_hz()
{
  if(file_test("sys/HZK16"))
    HZK = SD.open("sys/HZK16");
  if(file_test("sys/ASCII"))
    ASCII = SD.open("sys/ASCII");
  return;
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
