#ifndef BOOK_H
#define BOOK_H
uint32_t read_txt(char* txtname, uint32_t offset, int r, int g, int b, int dot);  //显示电子书内容
void into_book(char* txtname, uint32_t offset);  //打开电子书
void next_book(char* txtname);  //下一页
void last_book(char* txtname);  //上一页
uint32_t find_last_offset(char* txtname);  //查找上一页偏移
void exit_book();  //退出电子书
void into_book_config();  //打开电子书选项
void draw_book_config_point(int point, int r, int g, int b);  //画光标
void change_book_config_point();  //改变光标
void show_pallet(int point);  //打开调试板
void change_temp_rgb(int rgb, int point, int change);  //改变rgb
void change_pallet_point(int change);  //改变调色板光标
void change_dot(int change);  //改变字号
void change_offset(int change);  //改变电子书偏移
void exit_book_config();  //退出电子书选项
void check_txt_offset();
#endif
