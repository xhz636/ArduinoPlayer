#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "apgc.h"
#include "compiler.h"
int compiler(const char* apsc_name)
{
    FILE* apsc;
    FILE* apas;
    char apsc_line[4096];
    char apas_name[256];
    LineRead line_msg;
    struct Variable* all_var;
    struct Variable* cur;
    int i;
    int error = 0;
    int line_num = 0;
    int in_code = 0;
    int find_flag;
    if((apsc = fopen(apsc_name, "r")) == NULL)
    {
        printf("不能打开%s\n", apsc_name);
        return -1;
    }
    strcpy(apas_name, apsc_name);
    for(i = strlen(apas_name) - 1; i >= 0; i--)
        if(apas_name[i] == '.')
        {
            apas_name[i] == '\0';
            break;
        }
    strcat(apas_name, ".apas");
    if((apas = fopen(apas_name, "w")) == NULL)
    {
        printf("不能写入%s\n", apas_name);
        return -1;
    }
    all_var = read_variable(apsc);
    fseek(apsc, 0L, SEEK_SET);
    fseek(apas, 0L, SEEK_SET);
    while(fgets(apsc_line, 4096, apsc) != NULL)
    {
        line_num++;
        line_msg = read_line(apsc_line);
        if(line_msg.count == 0)
            continue;
        if(strcmp(line_msg.word[0], "code") == 0 && strcmp(line_msg.word[1], "segment") == 0)
        {
            in_code = 1;
            continue;
        }
        else if(strcmp(line_msg.word[0], "code") == 0 && strcmp(line_msg.word[1], "ends") == 0)
        {
            in_code = 0;
            continue;
        }
        if(!in_code)
            continue;
        else
        {
            find_flag = find_in_cmd(line_msg.word[0]);
            if(find_flag != -1)
                compile_cmd(line_msg, all_var, find_flag, apas);
            else
            {
                find_flag = find_in_fun(line_msg.word[0]);
                if(find_flag != -1)
                    compile_cmd(line_msg, all_var, find_flag, apas);
                else
                {
                    printf("在%d行出现未知符号！\n", line_num);
                    error++;
                }
            }
        }
    }
    fclose(apsc);
    fclose(apas);
    if(error)
    {
        remove(apas_name);
        printf("%d个错误！\n", error);
        return -1;
    }
    return 0;
}
struct Variable* read_variable(FILE* apsc)
{
    char apsc_line[4096];
    LineRead line_msg;
    struct Variable* head = NULL;
    struct Variable* pre = NULL;
    struct Variable* cur = NULL;
    int in_data;
    int unsigned_char_count = 0;
    int int_count = 0;
    int string_count = 0;
    int var_flag;
    int i, count_change;
    fseek(apsc, 0L, SEEK_SET);
    while(fgets(apsc_line, 4096, apsc) != NULL)
    {
        line_msg = read_line(apsc_line);
        if(line_msg.count == 0)
            continue;
        else if(strcmp(line_msg.word[0], "data") == 0 && strcmp(line_msg.word[1], "segment") == 0)
        {
            in_data = 1;
            continue;
        }
        else if(strcmp(line_msg.word[0], "data") == 0 && strcmp(line_msg.word[1], "ends") == 0)
        {
            in_data = 0;
            continue;
        }
        if(in_data && line_msg.count >= 2)
        {
            if(head == NULL)
            {
                head = (struct Variable*)malloc(sizeof(struct Variable));
                head -> next = NULL;
                cur = head;
            }
            else
            {
                pre = cur;
                cur = (struct Variable*)malloc(sizeof(struct Variable));
                pre -> next = cur;
                cur -> next = NULL;
            }
            for(i = 0; i < strlen(line_msg.word[1]) && line_msg.word[1][i] != '['; i++)
                cur -> name[i] = line_msg.word[1][i];
            cur -> name[i] = '\0';
            strcpy(cur -> type, line_msg.word[0]);
            if(line_msg.word[1][i] != '[')
                count_change = 1;
            else
                sscanf(line_msg.word[1] + i + 1, "%d", &count_change);
            switch(cur -> type[0])
            {
                case 'u': cur -> index = unsigned_char_count; unsigned_char_count += count_change; break;
                case 'i': cur -> index = int_count; int_count += count_change;break;
                case 's': cur -> index = string_count; string_count += count_change;break;
            }
        }
    }
    return head;
}
struct Variable* find_in_variable(const char* word, struct Variable* head)
{
    struct Variable* cur;
    for(cur = head; cur != NULL; cur = cur -> next)
        if(strcmp(word, cur -> name) == 0)
            return cur;
    return NULL;
}
int find_in_cmd(const char* word)
{
    char cmd[27][6] =
    {
        "dtc",
        "ctd",
        "atp",
        "mov",
        "add",
        "sub",
        "mul",
        "div",
        "mod",
        "shl",
        "shr",
        "and",
        "or",
        "xor",
        "cmp",
        "not",
        "inc",
        "dec",
        "jmp",
        "je",
        "jne",
        "jg",
        "jge",
        "jl",
        "jle",
        "call",
        "ret"
    };
    int i;
    for(i = 0; i < 27; i++)
        if(strcmp(word, cmd[i]) == 0)
            return i;
    return -1;
}
int find_in_fun(const char* word)
{
    char fun[32][16] =
    {
        "btnPress",
        "fillScr",
        "setColor",
        "drawPixel",
        "drawLine",
        "drawRect",
        "drawCircle",
        "fillRect",
        "fillCircle",
        "delay",
        "showAscii",
        "showEnglish",
        "showHZ",
        "showChinese",
        "openMap",
        "mapSeek",
        "mapPosition",
        "mapRead",
        "mapSize",
        "closeMap",
        "getMapAmount",
        "getMapFlag",
        "setMapFlag",
        "numPrintf",
        "setString",
        "strcpy",
        "strcat",
        "strcmp",
        "strlen",
        "updateSave",
        "updateMap",
        "exitGame"
    };
    int i;
    for(i = 0; i < 32; i++)
        if(strcmp(word, fun[i]) == 0)
            return i;
    return -1;
}
int find_in_var(const char* word)
{
    char var[38][16] =
    {
        "pin",
        "pressed",
        "color_r",
        "color_g",
        "color_b",
        "point_x1",
        "point_y1",
        "point_x2",
        "point_y2",
        "point_radius",
        "time_delay",
        "ascii",
        "english",
        "hz",
        "chinese",
        "dot",
        "map_index",
        "map_offset",
        "map_position",
        "map_read",
        "map_size",
        "map_amount",
        "map_x",
        "map_y",
        "map_xy_flag",
        "num",
        "str1",
        "str2",
        "str_cmp",
        "str_len",
        "all",
        "win",
        "lose",
        "index1",
        "index2",
        "unsigned_char",
        "int",
        "string"
    };
    int i;
    for(i = 0; i < 38; i++)
        if(strcmp(word, var[i]) == 0)
            return i;
    return -1;
}
void compile_cmd(LineRead line_msg, struct Variable* head, int cmd_flag, FILE* apas)
{
    char opt1[16];
    char opt2[16];
    char line[256];
    if(cmd_flag == 3 && line_msg.word[2][0] == '\"')
    {
        write_string(line_msg, head, apas);
        return;
    }
    else if(cmd_flag >= 0 && cmd_flag <= 17)
    {
        if(find_in_var(line_msg.word[1]) != -1)
            strcpy(opt1, line_msg.word[1]);
        else
            strcpy(opt1, compile_var(line_msg.word[1], head, 1, apas));
        if(cmd_flag <= 14)
        {
            if(is_const(line_msg.word[2]))
                strcpy(opt2, line_msg.word[2]);
            else
                strcpy(opt2, compile_var(line_msg.word[2], head, 2, apas));
            sprintf(line, "    %s %s %s\n", line_msg.word[0], opt1, opt2);
        }
        else
            sprintf(line, "    %s %s\n", line_msg.word[0], opt1);
    }
    else if(cmd_flag >= 18 && cmd_flag <= 25)
        sprintf(line, "    %s %s\n", line_msg.word[0], line_msg.word[1]);
    else if(cmd_flag == 26)
        sprintf(line, "    %s\n", line_msg.word[0]);
    fputs(line, apas);
    return;
}
void compile_fun(LineRead line_msg, struct Variable* head, int fun_flag, FILE* apas)
{
    LineRead mov_var;
    char mov_line[4096];
    char fun_line[256];
    if(line_msg.count == 1)
    {
        sprintf(fun_line, "    %s\n", line_msg.word[0]);
        fputs(fun_line, apas);
        return;
    }
    switch(fun_flag)
    {
        case 0: 
            if(strcmp(line_msg.word[1], "pin") != 0)
            {
                sprintf(mov_line, "mov pin %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 1: case 2:
            if(strcmp(line_msg.word[1], "color_r") != 0)
            {
                sprintf(mov_line, "mov color_r %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[2], "color_g") != 0)
            {
                sprintf(mov_line, "mov color_g %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[3], "color_b") != 0)
            {
                sprintf(mov_line, "mov color_b %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 3:
            if(strcmp(line_msg.word[1], "point_x1") != 0)
            {
                sprintf(mov_line, "mov point_x1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[2], "point_y1") != 0)
            {
                sprintf(mov_line, "mov point_y1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 4: case 5: case 7:
            if(strcmp(line_msg.word[1], "point_x1") != 0)
            {
                sprintf(mov_line, "mov point_x1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[2], "point_y1") != 0)
            {
                sprintf(mov_line, "mov point_y1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[3], "point_x2") != 0)
            {
                sprintf(mov_line, "mov point_x2 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[4], "point_y2") != 0)
            {
                sprintf(mov_line, "mov point_y2 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 6: case 8:
            if(strcmp(line_msg.word[1], "point_x1") != 0)
            {
                sprintf(mov_line, "mov point_x1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[2], "point_y1") != 0)
            {
                sprintf(mov_line, "mov point_y1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[3], "point_radius") != 0)
            {
                sprintf(mov_line, "mov point_radius %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 9:
            if(strcmp(line_msg.word[1], "time_delay") != 0)
            {
                sprintf(mov_line, "mov time_delay %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 10:
            if(strcmp(line_msg.word[1], "point_x1") != 0)
            {
                sprintf(mov_line, "mov point_x1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[2], "point_y1") != 0)
            {
                sprintf(mov_line, "mov point_y1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[3], "ascii") != 0)
            {
                sprintf(mov_line, "dtc ascii %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 0, apas);
            }
            if(strcmp(line_msg.word[4], "color_r") != 0)
            {
                sprintf(mov_line, "mov color_r %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[5], "color_g") != 0)
            {
                sprintf(mov_line, "mov color_g %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[6], "color_b") != 0)
            {
                sprintf(mov_line, "mov color_b %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[7], "dot") != 0)
            {
                sprintf(mov_line, "mov dot %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 11:
            if(strcmp(line_msg.word[1], "point_x1") != 0)
            {
                sprintf(mov_line, "mov point_x1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[2], "point_y1") != 0)
            {
                sprintf(mov_line, "mov point_y1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[3], "english") != 0)
            {
                sprintf(mov_line, "atp english %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 2, apas);
            }
            if(strcmp(line_msg.word[4], "color_r") != 0)
            {
                sprintf(mov_line, "mov color_r %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[5], "color_g") != 0)
            {
                sprintf(mov_line, "mov color_g %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[6], "color_b") != 0)
            {
                sprintf(mov_line, "mov color_b %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[7], "dot") != 0)
            {
                sprintf(mov_line, "mov dot %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 12:
            if(strcmp(line_msg.word[1], "point_x1") != 0)
            {
                sprintf(mov_line, "mov point_x1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[2], "point_y1") != 0)
            {
                sprintf(mov_line, "mov point_y1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[3], "hz") != 0)
            {
                sprintf(mov_line, "atp hz %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 2, apas);
            }
            if(strcmp(line_msg.word[4], "color_r") != 0)
            {
                sprintf(mov_line, "mov color_r %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[5], "color_g") != 0)
            {
                sprintf(mov_line, "mov color_g %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[6], "color_b") != 0)
            {
                sprintf(mov_line, "mov color_b %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[7], "dot") != 0)
            {
                sprintf(mov_line, "mov dot %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 13:
            if(strcmp(line_msg.word[1], "point_x1") != 0)
            {
                sprintf(mov_line, "mov point_x1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[2], "point_y1") != 0)
            {
                sprintf(mov_line, "mov point_y1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[3], "chinese") != 0)
            {
                sprintf(mov_line, "atp chinese %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 2, apas);
            }
            if(strcmp(line_msg.word[4], "color_r") != 0)
            {
                sprintf(mov_line, "mov color_r %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[5], "color_g") != 0)
            {
                sprintf(mov_line, "mov color_g %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[6], "color_b") != 0)
            {
                sprintf(mov_line, "mov color_b %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[7], "dot") != 0)
            {
                sprintf(mov_line, "mov dot %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 14:
            if(strcmp(line_msg.word[1], "map_index") != 0)
            {
                sprintf(mov_line, "mov map_index %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 15:
            if(strcmp(line_msg.word[1], "map_offset") != 0)
            {
                sprintf(mov_line, "mov map_offset %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 16: case 17: case 18: case 19: case 20:
            break;
        case 21:
            if(strcmp(line_msg.word[1], "map_x") != 0)
            {
                sprintf(mov_line, "mov map_x %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[2], "map_y") != 0)
            {
                sprintf(mov_line, "mov map_y %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 22:
            if(strcmp(line_msg.word[1], "map_x") != 0)
            {
                sprintf(mov_line, "mov map_x %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[2], "map_y") != 0)
            {
                sprintf(mov_line, "mov map_y %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[3], "map_xy_flag") != 0)
            {
                sprintf(mov_line, "mov map_xy_flag %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 23:
            if(strcmp(line_msg.word[1], "num") != 0)
            {
                sprintf(mov_line, "mov num %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[1], "str1") != 0)
            {
                sprintf(mov_line, "atp str1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 2, apas);
            }
            break;
        case 24:
            if(strcmp(line_msg.word[1], "str1") != 0)
            {
                sprintf(mov_line, "atp str1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 2, apas);
            }
            if(strcmp(line_msg.word[2], "index1") != 0)
            {
                sprintf(mov_line, "mov index1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[3], "ascii") != 0)
            {
                sprintf(mov_line, "dtc ascii %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 0, apas);
            }
            break;
        case 25: case 26: case 27:
            if(strcmp(line_msg.word[1], "str1") != 0)
            {
                sprintf(mov_line, "atp str1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 2, apas);
            }
            if(strcmp(line_msg.word[2], "str2") != 0)
            {
                sprintf(mov_line, "atp str2 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 2, apas);
            }
            break;
        case 28:
            if(strcmp(line_msg.word[1], "str1") != 0)
            {
                sprintf(mov_line, "atp str1 %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 2, apas);
            }
            break;
        case 29:
            if(strcmp(line_msg.word[1], "all") != 0)
            {
                sprintf(mov_line, "mov all %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[2], "win") != 0)
            {
                sprintf(mov_line, "mov win %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            if(strcmp(line_msg.word[3], "lose") != 0)
            {
                sprintf(mov_line, "mov lose %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 30:
            if(strcmp(line_msg.word[1], "map_index") != 0)
            {
                sprintf(mov_line, "mov map_index %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 31:
            break;
    }
    sprintf(fun_line, "    %s\n", line_msg.word[0]);
    fputs(fun_line, apas);
    switch(fun_flag)
    {
        case 0:
            if(strcmp(line_msg.word[2], "pressed") != 0)
            {
                sprintf(mov_line, "mov %s pressed\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 16:
            if(strcmp(line_msg.word[1], "map_position") != 0)
            {
                sprintf(mov_line, "mov %s map_position\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 17:
            if(strcmp(line_msg.word[1], "map_read") != 0)
            {
                sprintf(mov_line, "ctd %s map_read\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 1, apas);
            }
            break;
        case 18:
            if(strcmp(line_msg.word[1], "map_size") != 0)
            {
                sprintf(mov_line, "mov %s map_size\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 20:
            if(strcmp(line_msg.word[1], "map_amount") != 0)
            {
                sprintf(mov_line, "mov %s map_amount\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 21:
            if(strcmp(line_msg.word[3], "map_xy_flag") != 0)
            {
                sprintf(mov_line, "mov %s map_xy_flag\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 27:
            if(strcmp(line_msg.word[3], "str_cmp") != 0)
            {
                sprintf(mov_line, "mov str_cmp %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
        case 28:
            if(strcmp(line_msg.word[2], "str_len") != 0)
            {
                sprintf(mov_line, "mov str_len %s\n", line_msg.word[1]);
                mov_var = read_line(mov_line);
                compile_cmd(mov_var, head, 3, apas);
            }
            break;
    }
}
char* compile_var(const char* word, struct Variable* head, int which, FILE* apas)
{
    struct Variable* cur;
    char which_index[16];
    char line[256];
    char array_name[256];
    char array_index[256];
    int is_array = 0;
    int array_offset;
    int i;
    strcpy(array_name, word);
    for(i = 0; i < strlen(array_name); i++)
        if(array_name[i] == '[')
        {
            is_array = 1;
            array_name[i] = '\0';
            break;
        }
    if(is_array)
    {
        strcpy(array_index, array_name + i + 1);
        array_index[strlen(array_index) - 1] = '\0';
    }
    if(is_array)
    {
        if(isdigit(array_index[0]))
        {
            sscanf(array_index, "%d", &array_offset);
            cur = find_in_variable(array_name, head);
            sprintf(which_index, "index%d", which);
            sprintf(line, "    mov %s %d\n", which_index, cur -> index + array_offset);
            fputs(line, apas);
        }
        else
        {
            cur = find_in_variable(array_index, head);
            sprintf(line, "    mov index2 %d\n", which_index, cur -> index);
            fputs(line, apas);
            sprintf(line, "    mov index1 %s\n", cur -> type);
            cur = find_in_variable(array_name, head);
        }
    }
    else
    {
        cur = find_in_variable(word, head);
        sprintf(which_index, "index%d", which);
        sprintf(line, "    mov %s %d\n", which_index, cur ->index);
        fputs(line, apas);
    }
    return cur -> type;
}
void write_string(LineRead line_msg, struct Variable* head, FILE* apas)
{
    char string[256];
    int i;
    char line[256];
    struct Variable* var;
    strcpy(string, line_msg.word[2] + 1);
    string[strlen(string) - 1] = '\0';
    var = find_in_variable(line_msg.word[1], head);
    sprintf(line, "    mov index1 %d\n", var -> index);
    fputs(line, apas);
    fputs("    atp str1 string\n", apas);
    for(i = 0; i <= strlen(line); i++)
    {
        if(i == 0)
            fputs("    mov index1 0\n", apas);
        else
            fputs("    inc index1\n", apas);
        sprintf(line, "    mov num %d\n", line[i]);
        fputs(line, apas);
        fputs("    dtc ascii num\n", apas);
        fputs("    setString\n", apas);
    }
}
