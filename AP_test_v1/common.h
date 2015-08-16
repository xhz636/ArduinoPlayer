#ifndef COMMON_H
#define COMMON_H
#include <UTFT.h>
#include <SPI.h>
#include <SD.h>
extern UTFT myGLCD;
extern File HZK, ASCII;
extern int work;
extern int main_menu_point, file_list_point;
extern char file_list[9][16];
extern char book_name[32];
extern int txtfr, txtfg, txtfb, txtbr, txtbg, txtbb, txtdot;
extern uint32_t txt_last_offset, txt_now_offset, txt_next_offset;
extern const int btnUP;
extern const int btnDOWN;
extern const int btnLEFT;
extern const int btnRIGHT;
extern const int btnA;
extern const int btnB;
//extern const int btnSTART;
//extern const int btnSELECT;
enum WHERE
{
  MAIN_MENU,
  BOOK_MENU,
  BOOK_SHOW  
};
bool file_test(char* filename);
void read_file_list(char* dirname);
void show_ascii(int x, int y, char c, int r, int g, int b, int dot);
void show_english(int x, int y, char* sentence, int r, int g, int b, int dot);
void show_chinese(int x, int y, char* s, int r, int g, int b, int dot);
void change_file_list_point(int change);
void draw_file_list_point(int point, int r, int g, int b);
#endif
