#ifndef COMMON_H
#define COMMON_H
#include <UTFT.h>
#include <SPI.h>
#include <SD.h>
extern UTFT myGLCD;
extern File HZK, ASCII;
extern int work;
extern int main_menu_point, file_list_point, book_config_point;;
extern int file_amount, file_offset;
extern char file_list[9][16];
extern char book_name[32];
extern int txtfr, txtfg, txtfb, txtbr, txtbg, txtbb, txtdot;
extern uint32_t txt_last_offset, txt_now_offset, txt_next_offset, txt_max_offset;
extern int temp_r[2], temp_g[2], temp_b[2], temp_dot, temp_point;
extern uint32_t temp_offset_rate;
extern boolean in_pallet;
extern const int btnUP;
extern const int btnDOWN;
extern const int btnLEFT;
extern const int btnRIGHT;
extern const int btnA;
extern const int btnB;
extern const int btnSTART;
extern const int btnSELECT;
enum WHERE
{
  MAIN_MENU,
  BOOK_MENU,
  BOOK_SHOW,
  BOOK_CONFIG
};
bool file_test(char* filename);
int get_file_amount(char* dirname);
void read_file_list(char* dirname, int offset);
void show_file_menu();
void show_ascii(int x, int y, char c, int r, int g, int b, int dot);
void show_english(int x, int y, char* sentence, int r, int g, int b, int dot);
void show_chinese(int x, int y, char* s, int r, int g, int b, int dot);
void show_chinese_sentence(int x, int y, char* sentence, int r, int g, int b, int dot);
void change_file_list_point(int change);
void draw_file_list_point(int point, int r, int g, int b);
void print_message(int point, int x, int y, int r, int g, int b, int dot);
void print_size(int point, int x, int y, int r, int g, int b, int dot);
#endif
