#include "common.h"
#include "game_simulator.h"
#include "game.h"
unsigned char game_pin;
boolean game_pressed;
unsigned char game_color_r, game_color_g, game_color_b;
int game_point_x1, game_point_y1, game_point_x2, game_point_y2, game_point_radius;
int game_time_delay;
char game_ascii;
char* game_english;
char* game_hz;
char* game_chinese;
int game_dot;
int game_map_index;
uint32_t game_map_offset, game_map_position, game_map_size;
unsigned char game_map_read;
int game_map_amount;
char game_map_flag[22][17];
int game_map_x, game_map_y, game_map_xy_flag;
unsigned char game_num1;
unsigned short game_num2;
int game_num3;
uint32_t game_num4;
char* game_str1;
char* game_str2;
int game_str_cmp, game_str_len;
unsigned short game_all, game_win, game_lose;
unsigned char game_array;
File game_apg, game_map;
unsigned char var_unsigned_char[32];
boolean var_boolean[16];
int var_int[32];
uint32_t var_uint32_t[16];
double var_double[16];
char var_string[4][64];
unsigned char stack[1000];
int game_sp;
uint32_t game_ip;
void game_start()
{
  char apgname[32];
  myGLCD.fillScr(255, 255, 255);
  game_playing = true;
  game_sp = 0;
  sprintf(apgname, "%s/%s", game_name, "game.apg");
  if(!file_test(apgname))
    return;
  game_apg = SD.open(apgname);
  game_ip = read_uint32_t(0);
  game_start_time = millis();
  while(game_playing)
    read_apg();
  game_end_time = millis();
  game_apg.close();
  update_time(game_end_time - game_start_time);
  game_menu_point = 0;
  show_game_menu();
}
void read_apg()
{
  unsigned char flag;
  game_apg.seek(game_ip);
  flag = game_apg.read();
  if(flag == 0x01)
    read_cmd();
  else if(flag == 0x02)
    read_fun();
}
void read_cmd()
{
  int num;
  unsigned char cmd_flag;
  cmd_flag = game_apg.read();
}
void read_fun()
{
  unsigned char fun_flag;
  char mapname[32];
  fun_flag = game_apg.read();
  switch(fun_flag)
  {
    case BTN_PRESS: if(digitalRead(game_pin) == LOW)
                      game_pressed = true;
                    else
                      game_pressed = false;
                    break;
    case FILL_SCR: myGLCD.fillScr(game_color_r, game_color_g, game_color_b); break;
    case SET_COLOR: myGLCD.setColor(game_color_r, game_color_g, game_color_b); break;
    case DRAW_PIXEL: myGLCD.drawPixel(game_point_x1, game_point_y1); break;
    case DRAW_LINE: myGLCD.drawLine(game_point_x1, game_point_y1, game_point_x2, game_point_y2); break;
    case DRAW_RECT: myGLCD.drawRect(game_point_x1, game_point_y1, game_point_x2, game_point_y2); break;
    case DRAW_CIRCLE: myGLCD.drawCircle(game_point_x1, game_point_y1, game_point_radius); break;
    case FILL_RECT: myGLCD.fillRect(game_point_x1, game_point_y1, game_point_x2, game_point_y2); break;
    case FILL_CIRCLE: myGLCD.fillCircle(game_point_x1, game_point_y1, game_point_radius); break;
    case DELAY: delay(game_time_delay); break;
    case SHOW_ASCII: show_ascii(game_point_x1, game_point_y1, game_ascii, game_color_r, game_color_g, game_color_b, game_dot); break;
    case SHOW_ENGLISH: show_english(game_point_x1, game_point_y1, game_english, game_color_r, game_color_g, game_color_b, game_dot); break;
    case SHOW_HZ: show_chinese(game_point_x1, game_point_y1, game_hz, game_color_r, game_color_g, game_color_b, game_dot); break;
    case SHOW_CHINESE: show_chinese_sentence(game_point_x1, game_point_y1, game_chinese, game_color_r, game_color_g, game_color_b, game_dot);
    case OPEN_MAP:{
                    sprintf(mapname, "%s/map/%d.map", game_name, game_map_index);
                    game_map = SD.open(mapname);
                  }
                  break;
    case MAP_SEEK: game_map.seek(game_map_offset); break;
    case MAP_POSITION: game_map_position = game_map.position(); break;
    case MAP_READ: game_map_read = game_map.read(); break;
    case MAP_SIZE: game_map_size = game_map.size(); break;
    case CLOSE_MAP: game_map.close(); break;
    case GET_MAP_AMOUNT:{
                          sprintf(mapname, "%s/map", game_name);
                          game_map_amount = get_file_amount(mapname, ONLY_FILE);
                        }
                        break;
    case GET_MAP_FLAG: game_map_xy_flag = game_map_flag[game_map_x][game_map_y]; break;
    case SET_MAP_FLAG: game_map_flag[game_map_x][game_map_y] = game_map_xy_flag; break;
    case NUM_PRINTF_HHU: sprintf(game_str1, "%hhu", game_num1); break;
    case NUM_PRINTF_HU: sprintf(game_str1, "%hu", game_num2); break;
    case NUM_PRINTF_D: sprintf(game_str1, "%d", game_num3); break;
    case NUM_PRINTF_LU: sprintf(game_str1, "%lu", game_num4); break;
    case STR_CPY: strcpy(game_str1, game_str2); break;
    case STR_CAT: strcat(game_str1, game_str2); break;
    case STR_CMP: game_str_cmp = strcmp(game_str1, game_str2); break;
    case STR_LEN: game_str_len = strlen(game_str1); break;
    case UPDATE_SAVE: update_play(game_all, game_win, game_lose); break;
    case UPDATE_MAP: update_map(game_map_index); break;
    case EXIT_GAME: game_playing = false; break;
  }
  game_ip += 2;
}
int read_int(uint32_t offset)
{
  unsigned char temp[2];
  int result;
  game_apg.seek(offset);
  temp[0] = game_apg.read();
  temp[1] = game_apg.read();
  result = *((int*)temp);
  return result;
}
uint32_t read_uint32_t(uint32_t offset)
{
  unsigned char temp[4];
  uint32_t result;
  int i;
  game_apg.seek(offset);
  for(i = 0; i < 4; i++)
    temp[i] = game_apg.read();
  result = *((uint32_t*)temp);
  return result;
}
void ip_push()
{
  int i;
  for(i = 0; i < 4; i++)
    stack[game_sp + i] = *((unsigned char*)game_ip + i);
  game_sp += 4;
}
void ip_pop()
{
  unsigned char temp[4];
  int i;
  game_sp -= 4;
  for(i = 0; i < 4; i++)
    temp[i] = stack[game_sp + i];
  game_ip = *((uint32_t*)temp);
}

