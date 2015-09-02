#include "common.h"
#include "menu.h"
#include "about.h"
void show_main_menu()
{
  myGLCD.fillScr(255, 255, 255);
  show_apimg(0, 176 - 30, "sys/bottom.api");  //下方背景
  show_apimg(39 - 31, 39 - 31, "sys/book.api");  //电子书
  show_apimg(110 - 31, 39 - 31, "sys/music.api");  //音乐
  show_apimg(181 - 31, 39 - 31, "sys/image.api");  //图片
  show_apimg(39 -31, 110 - 31, "sys/game.api");  //游戏
  show_apimg(110 - 31, 110 - 31, "sys/file.api");  //文件
  show_apimg(181 - 31, 110 - 31, "sys/about.api");  //关于
  work = MAIN_MENU;
  main_menu_point = 0;
  draw_main_menu_point(main_menu_point, 255, 0, 0);
  return;
}
void show_apimg(int x, int y, char* apimgname)
{
  #ifndef DEBUG
  File apimg;
  unsigned char temp[2];
  unsigned short width, height, i, j;
  unsigned char r, g, b, a;
  if(!file_test(apimgname))
    return;
  apimg = SD.open(apimgname);
  temp[0] = apimg.read();
  temp[1] = apimg.read();
  width = *(unsigned short*)temp;  //读取图片宽度
  temp[0] = apimg.read();
  temp[1] = apimg.read();
  height = *(unsigned short*)temp;  //读取图片高度
  for(j = 0; j < height; j++)  //逐行描点
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
  #endif
}
void change_main_menu_point(int change_x, int change_y)
{
  draw_main_menu_point(main_menu_point, 255, 255, 255);
  if(change_x)
    main_menu_point = (main_menu_point / 3) * 3 + (main_menu_point + 3 + change_x) % 3;  //计算左右移动
  if(change_y)
    main_menu_point = (main_menu_point + 6 + change_y * 3) % 6;  //计算上下移动
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
void into_menu()
{
  char imagename[16];
  switch(main_menu_point)
  {
    case 0: work = BOOK_MENU;
            workdircase = ONLY_FILE;
            strcpy(workdirname, "book");
            strcpy(imagename, "sys/book.api");
            break;
    case 1: work = MUSIC_MENU;
            workdircase = ONLY_FILE;
            strcpy(workdirname, "/");
            strcpy(imagename, "sys/music.api");
            break;
    case 2: work = IMAGE_MENU;
            workdircase = ONLY_FILE;
            strcpy(workdirname, "image");
            strcpy(imagename, "sys/image.api");
            break;
    case 3: work = GAME_MENU;
            workdircase = ONLY_DIR;
            strcpy(workdirname, "game");
            strcpy(imagename, "sys/game.api");
            break;
    case 4: work = FILE_MENU;
            workdircase = BOTH_FILE_DIR;
            strcpy(workdirname, "/");
            strcpy(imagename, "sys/file.api");
            break;
    case 5: into_about();
            return;
  }
  myGLCD.fillScr(255, 255, 255);
  show_apimg(23, 23, imagename);  //显示图标
  file_amount = get_file_amount(workdirname, workdircase);  //文件数量
  file_offset = 0;
  read_file_list(workdirname, file_offset, workdircase);  //载入文件列表
  if(file_amount)
  {
    show_file_menu();  //显示文件列表
    file_list_point = 0;
    myGLCD.setColor(0, 0, 255);
    myGLCD.drawRect(210, 2, 218, 173);
    draw_file_list_point(file_list_point, 255, 0, 0);  //光标
  }
  else
    show_chinese_sentence(111, 4, "\xCE\xDE\xCE\xC4\xBC\xFE", 0, 0, 0, 1);  //无文件
  return;
}
void exit_menu()
{
  show_main_menu();
  return;
}
