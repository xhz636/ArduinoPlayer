#include "common.h"
#include "button.h"
#include "main_menu.h"
#include "book.h"
#include "book_menu.h"
void press_button()
{
  if(digitalRead(btnUP) == LOW)
    press_btnUP();
  if(digitalRead(btnDOWN) == LOW)
    press_btnDOWN();
  if(digitalRead(btnLEFT) == LOW)
    press_btnLEFT();
  if(digitalRead(btnRIGHT) == LOW)
    press_btnRIGHT();
  if(digitalRead(btnA) == LOW)
    press_btnA();
  if(digitalRead(btnB) == LOW)
    press_btnB();
//  if(digitalRead(btnSTART) == LOW)
//    press_btnSTART();
//  if(digitalRead(btnSELECT) == LOW)
//    press_btnSELECT();
}
void press_btnUP()
{
  switch(work)
  {
    case MAIN_MENU:change_main_menu_point(0, -1); break;
    case BOOK_MENU:change_file_list_point(-1); break;
    case BOOK_SHOW:last_book(book_name); break;
  }
}
void press_btnDOWN()
{
  switch(work)
  {
    case MAIN_MENU:change_main_menu_point(0, 1); break;
    case BOOK_MENU:change_file_list_point(1); break;
    case BOOK_SHOW:next_book(book_name); break;
  }
}
void press_btnLEFT()
{
  switch(work)
  {
    case MAIN_MENU:change_main_menu_point(-1, 0); break;
    case BOOK_SHOW:last_book(book_name); break;
  }
}
void press_btnRIGHT()
{
  switch(work)
  {
    case MAIN_MENU:change_main_menu_point(1, 0); break;
    case BOOK_SHOW:next_book(book_name); break;
  }
}
void press_btnA()
{
  switch(work)
  {
    case MAIN_MENU:if(main_menu_point == 0)into_book_menu(); break;
    case BOOK_MENU:{
                     strcpy(book_name, "txt/");
                     strcat(book_name, file_list[file_list_point]);
                     into_book(book_name, 0);
                     break;
                   }
  }
}
void press_btnB()
{
  switch(work)
  {
    case BOOK_MENU:exit_book_menu(); break;
    case BOOK_SHOW:exit_book(); break;
  }
}
