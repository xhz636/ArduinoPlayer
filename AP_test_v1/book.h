#ifndef BOOK_H
#define BOOK_H
void show_ascii(int x, int y, char c, int r, int g, int b, int dot);
void show_chinese(int x, int y, char* s, int r, int g, int b, int dot);
uint32_t read_txt(char* txtname, int offset, int r, int g, int b, int dot);
void into_book();
void next_book();
void last_book();
void exit_book();
#endif
