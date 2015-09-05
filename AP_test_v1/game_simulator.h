#ifndef GAME_SIMULATOR_H
#define GAME_SIMULATOR_H
extern unsigned char game_pin;
extern boolean game_pressed;
extern unsigned char game_color_r, game_color_g, game_color_b;
extern int game_point_x1, game_point_y1, game_point_x2, game_point_y2, game_point_radius;
extern int game_time_delay;
extern char game_ascii;
extern char* game_english;
extern char* game_hz;
extern char* game_chinese;
extern int game_dot;
extern int game_map_index;
extern uint32_t game_map_offset, game_map_position, game_map_size;
extern unsigned char game_map_read;
extern int game_map_amount;
extern char game_map_flag[22][17];
extern int game_map_x, game_map_y, game_map_xy_flag;
extern unsigned char game_num1;
extern unsigned short game_num2;
extern int game_num3;
extern uint32_t game_num4;
extern char* game_str1;
extern char* game_str2;
extern int game_str_cmp, game_str_len;
extern unsigned char game_array;
extern File game_apg, game_map;
extern unsigned char var_unsigned_char[32];
extern boolean var_boolean[16];
extern int var_int[32];
extern uint32_t var_uint32_t[16];
extern double var_double[16];
extern char var_string[4][64];
extern unsigned char stack[1000];
extern int game_sp;
extern uint32_t game_ip;
void game_start();
void read_apg();
void read_cmd();
void read_fun();
int read_int(uint32_t offset);
uint32_t read_uint32_t(uint32_t offset);
void ip_push();
void ip_pop();
enum CMD
{
    CMD_NONE = 0,
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
    NOT,
    SELF_INC,
    SELF_DEC,
    JMP,
    CMP,
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
    MAP_POSOTION,
    MAP_READ,
    MAP_SIZE,
    CLOSE_MAP,
    GET_MAP_AMOUNT,
    GET_MAP_FLAG,
    SET_MAP_FLAG,
    NUM_PRINTF_HHU,
    NUM_PRINTF_HU,
    NUM_PRINTF_D,
    NUM_PRINTF_LU,
    STR_CPY,
    STR_CAT,
    STR_CMP,
    STR_LEN,
    EXIT_GAME
};
enum VAR
{
    VAR_NONE1 = 0,
    VAR_PIN,
    VAR_PRESSED,
    VAR_COLOR_R,
    VAR_COLOR_G,
    VAR_COLOT_B,
    VAR_POINT_X1,
    VAR_POINT_Y1,
    VAR_POINT_X2,
    VAR_POINT_Y2,
    VAR_RADIUS,
    VAR_TIME_DELAY,
    VAR_ASCII,
    VAR_ENGLISH,
    VAR_HZ,
    VAR_CHINSES,
    VAR_DOT,
    VAR_MAP_INDEX,
    VAR_MAP_OFFSET,
    VAR_MAP_POSITION,
    VAR_MAP_READ,
    VAR_MAP_SIZE,
    VAR_MAP_AMOUNT,
    VAR_MAP_FLAG,
    VAR_MAP_X,
    VAR_MAP_Y,
    VAR_MAP_XY_FLAG,
    VAR_NUM1,
    VAR_NUM2,
    VAR_NUM3,
    VAR_NUM4,
    VAR_STR1,
    VAR_STR2,
    VAR_STR_CMP,
    VAR_STR_LEN,
    VAR_ARRAY,
    VAR_UNSIGNED_CHAR,
    VAR_BOOLEAN,
    VAR_INT,
    VAR_UINT32_T,
    VAR_DOUBLE,
    VAR_STRING
};
#endif
