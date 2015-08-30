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
  MAIN_MENU,  //主菜单
  BOOK_MENU,  //电子书文件列表
  BOOK_SHOW,  //电子书显示界面
  BOOK_CONFIG  //电子书选项界面
};
bool file_test(char* filename);  //测试文件
int get_file_amount(char* dirname);  //计算文件夹内文件数量
void read_file_list(char* dirname, int offset);  //载入文件列表
void show_file_menu();  //显示文件列表
void show_ascii(int x, int y, char c, int r, int g, int b, int dot);  //ASCII
void show_english(int x, int y, char* sentence, int r, int g, int b, int dot);  //英文句子
void show_chinese(int x, int y, char* s, int r, int g, int b, int dot);  //单个汉字
void show_chinese_sentence(int x, int y, char* sentence, int r, int g, int b, int dot);  //中文句子
void change_file_list_point(int change);  //改变光标
void draw_file_list_point(int point, int r, int g, int b);  //画光标
void print_message(int point, int x, int y, int r, int g, int b, int dot);  //输出信息
void print_size(int point, int x, int y, int r, int g, int b, int dot);  //输出文件大小
#endif
