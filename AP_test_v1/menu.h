#ifndef MENU_H
#define MENU_H
void show_main_menu();  //显示主菜单
void show_apimg(int x, int y, char* apimgname);  //显示标准图片
void change_main_menu_point(int change_x, int change_y);  //改变光标
void draw_main_menu_point(int point, int r, int g, int b);  //画光标
void into_book_menu();  //打开电子书文件列表
void exit_book_menu();  //退出电子书文件列表
void into_music_menu();  //打开音乐文件列表
void exit_music_menu();  //退出音乐文件列表
void into_image_menu();  //打开图片文件列表
void exit_image_menu();  //退出图片文件列表
void into_game_menu();  //打开游戏文件列表
void exit_game_menu();  //退出游戏文件列表
void into_file_menu();  //打开总文件列表
void exit_file_menu();  //退出总文件列表
#endif
