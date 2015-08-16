#include "common.h"
#include "book_menu.h"
#include "main_menu.h"
void into_book_menu()
{
  work = BOOK_MENU;
  read_file_list("txt");
  show_book_menu();
  file_list_point = 0;
  draw_file_list_point(file_list_point, 255, 0, 0);
  return;
}
void show_book_menu()
{
  int i;
  myGLCD.fillScr(255, 255, 255);
  show_apimg(23, 23, "sys/book.api");
  for(i = 0; i < 9; i++)
    show_english(111, 4 + 19 * i, file_list[i], 0, 0, 0, 1);
}
void exit_book_menu()
{
  show_main_menu();
  return;
}
