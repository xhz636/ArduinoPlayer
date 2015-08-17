#include "common.h"
#include "book_menu.h"
#include "main_menu.h"
void into_book_menu()
{
  work = BOOK_MENU;
  file_amount = get_file_amount("txt");
  file_offset = 0;
  read_file_list("txt", file_offset);
  myGLCD.fillScr(255, 255, 255);
  show_apimg(23, 23, "sys/book.api");
  show_file_menu();
  file_list_point = 0;
  draw_file_list_point(file_list_point, 255, 0, 0);
  return;
}
void exit_book_menu()
{
  show_main_menu();
  return;
}
