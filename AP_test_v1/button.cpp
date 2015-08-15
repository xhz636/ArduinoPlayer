#include "common.h"
#include "button.h"
#include "main_menu.h"
#include "book.h"
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
//  if(digitalRead(btnX) == LOW)
//    press_btnX();
//  if(digitalRead(btnY) == LOW)
//    press_btnY();
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
    case BOOK_SHOW:last_book(); break;
  }
}
void press_btnDOWN()
{
  switch(work)
  {
    case MAIN_MENU:change_main_menu_point(0, 1); break;
    case BOOK_SHOW:next_book(); break;
  }
}
void press_btnLEFT()
{
  switch(work)
  {
    case MAIN_MENU:change_main_menu_point(-1, 0); break;
    case BOOK_SHOW:last_book(); break;
  }
}
void press_btnRIGHT()
{
  switch(work)
  {
    case MAIN_MENU:change_main_menu_point(1, 0); break;
    case BOOK_SHOW:next_book(); break;
  }
}
void press_btnA()
{
  switch(work)
  {
    case MAIN_MENU:if(main_menu_point == 0)into_book(); break;
  }
}
void press_btnB()
{
  switch(work)
  {
    case BOOK_SHOW:exit_book(); break;
  }
}
