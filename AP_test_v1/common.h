#ifndef COMMON_H
#define COMMON_H
#include <UTFT.h>
#include <SPI.h>
#include <SD.h>
extern UTFT myGLCD;
extern File HZK, ASCII;
extern int work;
extern int main_menu_point;
extern uint32_t txt_last_offset, txt_now_offset, txt_next_offset;
extern const int btnUP;
extern const int btnDOWN;
extern const int btnLEFT;
extern const int btnRIGHT;
extern const int btnA;
extern const int btnB;
//extern const int btnX;
//extern const int btnY;
//extern const int btnSTART;
//extern const int btnSELECT;
enum WHERE
{
  MAIN_MENU,
  BOOK_SHOW,
  BOOK_MENU
};
bool file_test(char* filename);
#endif
