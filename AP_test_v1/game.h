#ifndef GAME_H
#define GAME_H
void into_game(char* gamename);
void exit_game();
void show_game_menu();
void draw_game_menu_point(int point, int r, int g, int b);
void change_game_menu_point(int change);
void show_game_save();
void show_game_help();
void show_clear();
void choose_no_clear();
void choose_yes_clear();
void clear_save();
void clear_cancel();
void update_play(unsigned short all, unsigned short win, unsigned lose);
void update_time(uint32_t playtime);
void update_map(int index);
#endif
