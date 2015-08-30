#include "common.h"
#include "book_menu.h"
#include "main_menu.h"
void into_book_menu()
{
  work = BOOK_MENU;
  file_amount = get_file_amount("txt");  //txt文件夹内文件数量
  file_offset = 0;
  read_file_list("txt", file_offset);  //载入文件列表
  myGLCD.fillScr(255, 255, 255);
  show_apimg(23, 23, "sys/book.api");  //显示图标
  show_file_menu();  //显示文件列表
  file_list_point = 0;
  draw_file_list_point(file_list_point, 255, 0, 0);  //光标
  return;
}
void exit_book_menu()
{
  show_main_menu();
  return;
}
