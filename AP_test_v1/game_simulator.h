#ifndef GAME_SIMULATOR_H
#define GAME_SIMULATOR_H
extern int game_pin, game_pressed;
extern int game_color_r, game_color_g, game_color_b;
extern int game_point_x1, game_point_y1, game_point_x2, game_point_y2, game_point_radius;
extern int game_time_delay;
extern unsigned char game_ascii;
extern char* game_english;
extern char* game_hz;
extern char* game_chinese;
extern int game_dot;
extern int game_map_index, game_map_offset, game_map_position, game_map_size, game_map_amount;
extern unsigned char game_map_read;
extern unsigned char game_map_flag[22][17];
extern int game_map_x, game_map_y;
extern unsigned char game_map_xy_flag;
extern int game_num;
extern char* game_str1;
extern char* game_str2;
extern int game_str_cmp, game_str_len;
extern int game_all, game_win, game_lose;
extern int game_index1, game_index2;
extern File game_apg, game_map;
extern unsigned char var_unsigned_char[32];
extern int var_int[64];
extern char var_string[4][64];
extern unsigned char stack[1000];
extern int game_sp;
extern uint32_t game_ip;
extern int game_cmp_result;
extern void* game_var_pointer;
void game_start();
void read_apg();
void read_cmd();
void read_fun();
int read_int(uint32_t offset);
uint32_t read_uint32_t(uint32_t offset);
void ip_push();
void ip_pop();
void* get_var_pointer(unsigned char var_name, int var_index);
void get_cmp_result(int num1, int num2);
enum CMD
{
    CMD_NONE = 0,
    DTC,
    CTD,
    ATP,
    MOV_NUM,
    MOV_VAR,
    ADD_NUM,
    ADD_VAR,
    SUB_NUM,
    SUB_VAR,
    MUL_NUM,
    MUL_VAR,
    DIV_NUM,
    DIV_VAR,
    MOD_NUM,
    MOD_VAR,
    SHL_NUM,
    SHL_VAR,
    SHR_NUM,
    SHR_VAR,
    AND_NUM,
    AND_VAR,
    OR_NUM,
    OR_VAR,
    XOR_NUM,
    XOR_VAR,
    CMP_NUM,
    CMP_VAR,
    NOT,
    SELF_INC,
    SELF_DEC,
    JMP,
    JE,
    JNE,
    JG,
    JGE,
    JL,
    JLE,
    CALL,
    RET
};
enum FUN
{
    FUN_NONE = 0,
    BTN_PRESS,
    FILL_SCR,
    SET_COLOR,
    DRAW_PIXEL,
    DRAW_LINE,
    DRAW_RECT,
    DRAW_CIRCLE,
    FILL_RECT,
    FILL_CIRCLE,
    DELAY,
    SHOW_ASCII,
    SHOW_ENGLISH,
    SHOW_HZ,
    SHOW_CHINESE,
    OPEN_MAP,
    MAP_SEEK,
    MAP_POSITION,
    MAP_READ,
    MAP_SIZE,
    CLOSE_MAP,
    GET_MAP_AMOUNT,
    GET_MAP_FLAG,
    SET_MAP_FLAG,
    NUM_PRINTF,
    SET_STRING,
    STR_CPY,
    STR_CAT,
    STR_CMP,
    STR_LEN,
    UPDATE_SAVE,
    UPDATE_MAP,
    EXIT_GAME
};
enum VAR
{
    VAR_NONE = 0,
    VAR_PIN,
    VAR_PRESSED,
    VAR_COLOR_R,
    VAR_COLOR_G,
    VAR_COLOR_B,
    VAR_POINT_X1,
    VAR_POINT_Y1,
    VAR_POINT_X2,
    VAR_POINT_Y2,
    VAR_RADIUS,
    VAR_TIME_DELAY,
    VAR_ASCII,
    VAR_ENGLISH,
    VAR_HZ,
    VAR_CHINESE,
    VAR_DOT,
    VAR_MAP_INDEX,
    VAR_MAP_OFFSET,
    VAR_MAP_POSITION,
    VAR_MAP_READ,
    VAR_MAP_SIZE,
    VAR_MAP_AMOUNT,
    VAR_MAP_X,
    VAR_MAP_Y,
    VAR_MAP_XY_FLAG,
    VAR_NUM,
    VAR_STR1,
    VAR_STR2,
    VAR_STR_CMP,
    VAR_STR_LEN,
    VAR_ALL,
    VAR_WIN,
    VAR_LOSE,
    VAR_INDEX1,
    VAR_INDEX2,
    VAR_UNSIGNED_CHAR,
    VAR_INT,
    VAR_STRING
};
enum CMP
{
  EQUAL = 0x01,
  NOT_EQUAL = 0x02,
  GREATER = 0x04,
  LESS = 0x08
};
#endif
