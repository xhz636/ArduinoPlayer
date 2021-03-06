#ifndef MUSIC_H
#define MUSIC_H
int freeRam();
void show_freeram();
void into_music(char* musicname);
void exit_music();
void draw_music_play();
void show_music_state();
void draw_music_state(int r, int g, int b);
void show_music_mode();
void draw_music_mode(int r, int g, int b);
void show_music_help();
void change_music_state();
void change_music_mode();
void check_music();
void next_music();
void find_next_music(int amount, int offset);
void change_music(char* musicname);
void change_next_music(int change);
void stop_music();
#endif
