#ifndef BOOK_H
#define BOOK_H
uint32_t read_txt(char* txtname, int offset, int r, int g, int b, int dot);
void into_book(char* txtname, uint32_t offset);
void next_book(char* txtname);
void last_book(char* txtname);
uint32_t find_last_offset(char* txtname);
void exit_book();
#endif
