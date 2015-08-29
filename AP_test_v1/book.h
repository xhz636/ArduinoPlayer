#ifndef BOOK_H
#define BOOK_H
uint32_t read_txt(char* txtname, int offset, int r, int g, int b, int dot);
void into_book(char* txtname, uint32_t offset);
void next_book(char* txtname);
void last_book(char* txtname);
uint32_t find_last_offset(char* txtname);
void exit_book();
void into_book_config();
void draw_book_config_point(int point, int r, int g, int b);
void change_book_config_point();
void show_pallet(int point);
void change_temp_rgb(int rgb, int point, int change);
void change_pallet_point(int change);
void change_dot(int change);
void change_offset(int change);
void exit_book_config();
#endif
