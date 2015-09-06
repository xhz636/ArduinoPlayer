#include "common.h"
#include "game_simulator.h"
#include "game.h"
int game_pin, game_pressed;
int game_color_r, game_color_g, game_color_b;
int game_point_x1, game_point_y1, game_point_x2, game_point_y2, game_point_radius;
int game_time_delay;
unsigned char game_ascii;
char* game_english;
char* game_hz;
char* game_chinese;
int game_dot;
int game_map_index, game_map_offset, game_map_position, game_map_size, game_map_amount;
unsigned char game_map_read;
unsigned char game_map_flag[22][17];
int game_map_x, game_map_y;
unsigned char game_map_xy_flag;
int game_num;
char* game_str1;
char* game_str2;
int game_str_cmp, game_str_len;
int game_all, game_win, game_lose;
int game_index1, game_index2;
File game_apg, game_map;
unsigned char var_unsigned_char[32];
int var_int[64];
char var_string[4][64];
unsigned char stack[1000];
int game_sp;
uint32_t game_ip;
int game_cmp_result;
void* game_var_pointer;
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
  {
    #ifdef DEBUG
    Serial.println(game_ip, HEX);
    #endif
    read_apg();
  }
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
  uint32_t sign;
  unsigned char cmd_flag, var_name;
  void* var[2];
  cmd_flag = game_apg.read();
  if(cmd_flag >= DTC && cmd_flag <= SELF_DEC)
  {
    var_name = game_apg.read();
    var[0] = get_var_pointer(var_name, game_index1);
    game_ip += 3;
    if(cmd_flag >= DTC && cmd_flag <= ATP)
    {
      var_name = game_apg.read();
      var[1] = get_var_pointer(var_name, game_index2);
      game_ip += 1;
    }
    else if(cmd_flag >= MOV_NUM && cmd_flag <= CMP_VAR)
    {
      if(cmd_flag % 2 == 0)
      {
        num = read_int(game_ip);
        game_ip += 2;
      }
      else
      {
        var_name = game_apg.read();
        var[1] = get_var_pointer(var_name, game_index2);
        game_ip += 1;
      }
    }
  }
  else if(cmd_flag >= JMP && cmd_flag <= CALL)
  {
    sign = read_uint32_t(game_ip + 2);
    game_ip += 6;
  }
  switch(cmd_flag)
  {
    case DTC: *(unsigned char*)var[0] = (unsigned char)(*(int*)var[1] & 0xFF); break;
    case CTD: *(int*)var[0] = (int)(*(unsigned char*)var[1]); break;
    case ATP: *(char**)var[0] = (char*)var[1]; break;
    case MOV_NUM: *(int*)var[0] = num; break;
    case MOV_VAR: *(int*)var[0] = *(int*)var[1]; break;
    case ADD_NUM: *(int*)var[0] += num; break;
    case ADD_VAR: *(int*)var[0] += *(int*)var[1]; break;
    case SUB_NUM: *(int*)var[0] -= num; break;
    case SUB_VAR: *(int*)var[0] -= *(int*)var[1]; break;
    case MUL_NUM: *(int*)var[0] *= num; break;
    case MUL_VAR: *(int*)var[0] *= *(int*)var[1]; break;
    case DIV_NUM: *(int*)var[0] /= num; break;
    case DIV_VAR: *(int*)var[0] /= *(int*)var[1]; break;
    case MOD_NUM: *(int*)var[0] %= num; break;
    case MOD_VAR: *(int*)var[0] %= *(int*)var[1]; break;
    case SHL_NUM: *(int*)var[0] <<= num; break;
    case SHL_VAR: *(int*)var[0] <<= *(int*)var[1]; break;
    case SHR_NUM: *(int*)var[0] >>= num; break;
    case SHR_VAR: *(int*)var[0] >>= *(int*)var[1]; break;
    case AND_NUM: *(int*)var[0] &= num; break;
    case AND_VAR: *(int*)var[0] &= *(int*)var[1]; break;
    case OR_NUM: *(int*)var[0] |= num; break;
    case OR_VAR: *(int*)var[0] |= *(int*)var[1]; break;
    case XOR_NUM: *(int*)var[0] ^= num; break;
    case XOR_VAR: *(int*)var[0] ^= *(int*)var[1]; break;
    case CMP_NUM: get_cmp_result(*(int*)var[0], num); break;
    case CMP_VAR: get_cmp_result(*(int*)var[0], *(int*)var[1]); break;
    case NOT: *(int*)var[0] = ~(*(int*)var[0]); break;
    case SELF_INC: (*(int*)var[0])++; break;
    case SELF_DEC: (*(int*)var[0])--; break;
    case JMP: game_ip = sign; break;
    case JE: if(game_cmp_result & EQUAL)
               game_ip = sign;
             break;
    case JNE: if(game_cmp_result & NOT_EQUAL)
                game_ip = sign;
              break;
    case JG: if(game_cmp_result & GREATER)
               game_ip = sign;
             break;
    case JGE: if(game_cmp_result & GREATER_EQUAL)
                game_ip = sign;
              break;
    case JL: if(game_cmp_result & LESS)
               game_ip = sign;
             break;
    case JLE: if(game_cmp_result & LESS_EQUAL)
                game_ip = sign;
              break;
    case CALL: ip_push();
               game_ip = sign;
               break;
    case RET: ip_pop();
              break;
  }
}
void read_fun()
{
  unsigned char fun_flag;
  char mapname[32];
  fun_flag = game_apg.read();
  switch(fun_flag)
  {
    case BTN_PRESS: if(digitalRead(game_pin) == LOW)
                      game_pressed = 1;
                    else
                      game_pressed = 0;
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
    case NUM_PRINTF: sprintf(game_str1, "%d", game_num); break;
    case SET_STRING: game_str1[game_index1] = game_ascii; break;
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
  {
    stack[game_sp + i] = *((unsigned char*)&game_ip + i);
    #ifdef DEBUG
    Serial.println(stack[game_sp + i], HEX);
    #endif
  }
  game_sp += 4;
}
void ip_pop()
{
  unsigned char temp[4];
  int i;
  game_sp -= 4;
  for(i = 0; i < 4; i++)
  {
    temp[i] = stack[game_sp + i];
    #ifdef DEBUG
    Serial.println(stack[game_sp + i], HEX);
    #endif
  }
  game_ip = *((uint32_t*)temp);
}
void* get_var_pointer(unsigned char var_name, int var_index)
{
  void* result;
  switch(var_name)
  {
    case VAR_PIN: result = (void*)(&game_pin); break;
    case VAR_PRESSED: result = (void*)(&game_pressed); break;
    case VAR_COLOR_R: result = (void*)(&game_color_r); break;
    case VAR_COLOR_G: result = (void*)(&game_color_g); break;
    case VAR_COLOR_B: result = (void*)(&game_color_b); break;
    case VAR_POINT_X1: result = (void*)(&game_point_x1); break;
    case VAR_POINT_Y1: result = (void*)(&game_point_y1); break;
    case VAR_POINT_X2: result = (void*)(&game_point_x2); break;
    case VAR_POINT_Y2: result = (void*)(&game_point_y2); break;
    case VAR_RADIUS: result = (void*)(&game_point_radius); break;
    case VAR_TIME_DELAY: result = (void*)(&game_time_delay); break;
    case VAR_ASCII: result = (void*)(&game_ascii); break;
    case VAR_ENGLISH: result = (void*)(&game_english); break;
    case VAR_HZ: result = (void*)(&game_hz); break;
    case VAR_CHINESE: result = (void*)(&game_chinese); break;
    case VAR_DOT: result = (void*)(&game_dot); break;
    case VAR_MAP_INDEX: result = (void*)(&game_map_index); break;
    case VAR_MAP_OFFSET: result = (void*)(&game_map_offset); break;
    case VAR_MAP_POSITION: result = (void*)(&game_map_position); break;
    case VAR_MAP_READ: result = (void*)(&game_map_read); break;
    case VAR_MAP_SIZE: result = (void*)(&game_map_size); break;
    case VAR_MAP_AMOUNT: result = (void*)(&game_map_amount); break;
    case VAR_MAP_X: result = (void*)(&game_map_x); break;
    case VAR_MAP_Y: result = (void*)(&game_map_y); break;
    case VAR_MAP_XY_FLAG: result = (void*)(&game_map_xy_flag); break;
    case VAR_NUM: result = (void*)(&game_num); break;
    case VAR_STR1: result = (void*)(&game_str1); break;
    case VAR_STR2: result = (void*)(&game_str2); break;
    case VAR_STR_CMP: result = (void*)(&game_str_cmp); break;
    case VAR_STR_LEN: result = (void*)(&game_str_len); break;
    case VAR_ALL: result = (void*)(&game_all); break;
    case VAR_WIN: result = (void*)(&game_win); break;
    case VAR_LOSE: result = (void*)(&game_lose); break;
    case VAR_INDEX1: result = (void*)(&game_index1); break;
    case VAR_INDEX2: result = (void*)(&game_index2); break;
    case VAR_UNSIGNED_CHAR: result = (void*)(&var_unsigned_char[var_index]); break;
    case VAR_INT: result = (void*)(&var_int[var_index]); break;
    case VAR_STRING: result = (void*)var_string[var_index]; break;
  }
  return result;
}
void get_cmp_result(int num1, int num2)
{
  game_cmp_result = 0;
  if(num1 == num2)
  {
    game_cmp_result |= EQUAL;
    game_cmp_result |= GREATER_EQUAL;
    game_cmp_result |= LESS_EQUAL;
  }
  else
  {
    game_cmp_result |= NOT_EQUAL;
    if(num1 > num2)
      game_cmp_result |= GREATER;
    else
      game_cmp_result |= LESS;
  }
}

