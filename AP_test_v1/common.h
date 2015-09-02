#ifndef COMMON_H
#define COMMON_H
//#define DEBUG
#include <UTFT.h>
#include <SPI.h>
#include <SD.h>
#include <SimpleSDAudio.h>
// Create static buffer 
#define BIGBUFSIZE (2*512)
extern uint8_t bigbuf[BIGBUFSIZE];
extern UTFT myGLCD;
extern File HZK, ASCII;
extern int work;
extern char workdirname[128];
extern int workdircase;
extern int main_menu_point, file_list_point, book_config_point;;
extern int file_amount, file_offset;
extern char file_list[9][16];
extern char book_name[32];
extern int txtfr, txtfg, txtfb, txtbr, txtbg, txtbb, txtdot;
extern uint32_t txt_now_offset, txt_next_offset, txt_max_offset;
extern int temp_r[2], temp_g[2], temp_b[2], temp_dot, temp_point;
extern uint32_t temp_offset_rate;
extern boolean in_pallet;
extern boolean txt_offset_changed;
extern char music_name[16];
extern boolean music_success;
extern int music_state, music_mode;
extern int music_amount, music_offset;
extern char image_name[32];
extern int image_mode, image_state, image_temp_mode;
extern int image_left_offset, image_top_offset, image_temp_left_offset, image_temp_top_offset;
extern unsigned short image_width, image_height;
extern int image_width_insample, image_height_insample;
extern int image_point;
extern int image_amount, image_offset;
extern double image_sample;
extern int file_delete_point;
extern int about_menu_point, about_help_point;
extern const int btnUP;
extern const int btnDOWN;
extern const int btnLEFT;
extern const int btnRIGHT;
extern const int btnA;
extern const int btnB;
extern const int btnSTART;
extern const int btnSELECT;
extern const int battery;
enum WHERE
{
  MAIN_MENU,  //主菜单
  BOOK_MENU,  //电子书文件列表
  BOOK_SHOW,  //电子书显示界面
  BOOK_CONFIG,  //电子书选项界面
  MUSIC_MENU,  //音乐文件列表
  MUSIC_PLAY,  //音乐播放界面
  IMAGE_MENU,  //图片文件列表
  IMAGE_SHOW,  //图片显示界面
  GAME_MENU,  //游戏文件列表
  FILE_MENU,  //总文件列表
  FILE_DELETE,  //文件删除界面
  ABOUT_MENU,  //关于界面
  ABOUT_HELP,  //帮助界面
  ABOUT_AP  //系统信息界面
};
enum SHOWDIR
{
  ONLY_FILE,  //只显示文件
  ONLY_DIR,  //只显示文件夹
  BOTH_FILE_DIR  //全部显示
};
enum MUSICSTATE
{
  ISPLAY,  //播放
  ISPAUSE,  //暂停
  ISSTOP  //停止
};
enum MUSICMODE
{
  SINGLE,  //单曲循环
  ORDER,  //顺序循环
  RANDOM  //随机播放
};
enum IMAGEMODE
{
  AUTOSIZE,  //自动适应屏幕
  FULLSIZE,  //原始比例
  HALFSIZE,  //50%比例
  QTRSIZE  //25%比例
};
enum IMAGESTATE
{
  NORMAL,  //原始位置
  LEFTSPIN,  //逆时针
  RIGHTSPIN,  //顺时针
  SEMISPIN  //旋转半周
};
bool file_test(char* filename);  //测试文件
int get_file_amount(char* dirname, int showdir);  //计算文件夹内文件数量
void read_file_list(char* dirname, int offset, int showdir);  //载入文件列表
void show_file_menu();  //显示文件列表
void show_ascii(int x, int y, char c, int r, int g, int b, int dot);  //ASCII
void show_english(int x, int y, char* sentence, int r, int g, int b, int dot);  //英文句子
void show_chinese(int x, int y, char* s, int r, int g, int b, int dot);  //单个汉字
void show_chinese_sentence(int x, int y, char* sentence, int r, int g, int b, int dot);  //中文句子
void change_file_list_point(int change);  //改变光标
void draw_file_list_point(int point, int r, int g, int b);  //画光标
void print_message(char* filename, int x, int y, int r, int g, int b, int dot);  //输出信息
void print_size(char* filename, int x, int y, int r, int g, int b, int dot);  //输出文件大小
void print_music_long(char* filename, int x, int y, int r, int g, int b, int dot);  //输出音乐长度
void read_image_size(char* imagename);
void print_image_size(char* filename, int x, int y, int r, int g, int b, int dot);  //输出图片大小
#endif
