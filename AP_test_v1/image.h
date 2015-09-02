#ifndef IMAGE_H
#define IMAGE_H
void into_image(char* imagename);
void exit_image();
void draw_image_show();
void clr_image();
void draw_image_point(int point, int r, int g, int b);
void change_image_point(int change);
void show_image_mode(int r, int g, int b);
void show_image_temp_mode(int r, int g, int b);
void show_image_left(int r, int g, int b);
void show_image_top(int r, int g, int b);
void change_image_mode(int change);
void change_image_left(int change);
void change_image_top(int change);
void image_update();
void image_left_spin();
void image_right_spin();
void find_image(int amount, int offset);
void clr_msg();
void image_next(int change);
void show_image(char* imagename, int mode, int state, int left, int top);
void mode2sample(int mode, int state);
uint32_t find_image_offset(int x, int y, int state, int left, int top, int width, int height);
#endif
