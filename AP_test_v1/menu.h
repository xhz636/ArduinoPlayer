#ifndef MENU_H
#define MENU_H
void show_main_menu();  //显示主菜单
void show_apimg(int x, int y, char* apimgname);  //显示标准图片
void change_main_menu_point(int change_x, int change_y);  //改变光标
void draw_main_menu_point(int point, int r, int g, int b);  //画光标
void into_menu();  //打开文件列表
void exit_menu();  //退出文件列表
#endif
