#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "apgc.h"
#include "assembler.h"
int assembler(const char* apas_name)
{
    FILE* apas;
    FILE* apg;
    struct Sign* all_sign;
    char apas_line[4096];
    LineRead line_msg;
    int error = 0;
    int line_num = 0;
    unsigned char write_char;
    short int write_num;
    unsigned long begin, offset;
    int cmd_flag;
    const char cmd_asm = 1;
    const char fun_asm = 2;
    if((apas = fopen(apas_name, "r")) == NULL)
    {
        printf("不能打开%s\n", apas_name);
        return -1;
    }
    if((apg = fopen("game.apg", "wb")) == NULL)
    {
        printf("不能写入%s\n", apas_name);
        return -1;
    }
    all_sign = read_sign(apas);
    fseek(apas, 0L, SEEK_SET);
    fseek(apg, 0L, SEEK_SET);
    fwrite(&begin, sizeof(begin), 1, apg);
    while(fgets(apas_line, 4096, apas) != NULL)
    {
        line_num++;
        line_msg = read_line(apas_line);
        if(line_msg.word[0][strlen(line_msg.word[0]) - 1] == ':' || line_msg.count == 0 ||
                strcmp(line_msg.word[1], "proc") == 0 || strcmp(line_msg.word[1], "endp") == 0 ||
                strcmp(line_msg.word[0], "code") == 0 && strcmp(line_msg.word[1], "segment") ||
                strcmp(line_msg.word[0], "code") == 0 && strcmp(line_msg.word[1], "ends"))
            continue;
        else if((write_char = assemble_cmd(line_msg.word[0], line_msg)) != 0)
        {
            fwrite(&cmd_asm, sizeof(cmd_asm), 1, apg);
            fwrite(&write_char, sizeof(write_char), 1, apg);
            cmd_flag = asm_find_in_cmd(line_msg.word[0], line_msg);
            if(cmd_flag >= 3 && cmd_flag <= 5)
            {
                write_char = assemble_var(line_msg.word[1]);
                fwrite(&write_char, sizeof(write_char), 1, apg);
                if(write_char == 0)
                {
                    printf("在%d行出现未知符号！\n", line_num);
                    error++;
                }
                if(cmd_flag == 4)
                {
                    write_char = assemble_var(line_msg.word[2]);
                    fwrite(&write_char, sizeof(write_char), 1, apg);
                    if(write_char == 0)
                    {
                        printf("在%d行出现未知符号！\n", line_num);
                        error++;
                    }
                }
                else if(cmd_flag == 5)
                {
                    write_num = read_const(line_msg.word[2]);
                    fwrite(&write_num, sizeof(write_num), 1, apg);
                }
            }
            else if(cmd_flag == 6)
            {
                offset = find_in_sign(line_msg.word[1], all_sign);
                fwrite(&offset, sizeof(offset), 1, apg);
                if(offset == -1)
                {
                    printf("在%d行出现未知符号！\n", line_num);
                    error++;
                }
            }
        }
        else if((write_char = assemble_fun(line_msg.word[0])) != 0)
        {
            fwrite(&fun_asm, sizeof(fun_asm), 1, apg);
            fwrite(&write_char, sizeof(write_char), 1, apg);
        }
        else if(strcmp(line_msg.word[0], "end") == 0)
        {
            fseek(apg, 0L, SEEK_SET);
            begin = find_in_sign(line_msg.word[1], all_sign);
            fwrite(&begin, sizeof(begin), 1, apg);
        }
        else
        {
            printf("在%d行出现未知符号\n", line_num);
            error++;
        }
    }
    fclose(apas);
    fclose(apg);
    if(error)
    {
        remove("game.apg");
        printf("%d个错误！\n", error);
        return -1;
    }
    return 0;
}
struct Sign* read_sign(FILE* apas)
{
    int offset = 0;
    char apas_line[4096];
    LineRead line_msg;
    struct Sign* head = NULL;
    struct Sign* pre = NULL;
    struct Sign* cur = NULL;
    int line_num = 0;
    fseek(apas, 0L, SEEK_SET);
    while(fgets(apas_line, 4096, apas) != NULL)
    {
        line_num++;
        line_msg = read_line(apas_line);
        if(line_msg.word[0][strlen(line_msg.word[0]) - 1] == ':' || strcmp(line_msg.word[1], "proc") == 0)
        {
            if(line_msg.word[0][strlen(line_msg.word[0]) - 1] == ':')
                line_msg.word[0][strlen(line_msg.word[0]) - 1] = '\0';
            if(head == NULL)
            {
                head = (struct Sign*)malloc(sizeof(struct Sign));
                head -> next = NULL;
                cur = head;
            }
            else
            {
                pre = cur;
                cur = (struct Sign*)malloc(sizeof(struct Sign));
                pre -> next = cur;
                cur -> next = NULL;
            }
            strcpy(cur -> name, line_msg.word[0]);
            cur -> offset = offset + 4;
            continue;
        }
        else
            offset += read_offset(line_msg);
    }
    return head;
}
int read_offset(LineRead line_msg)
{
    int offset = 0;
    offset += asm_find_in_cmd(line_msg.word[0], line_msg);
    offset += asm_find_in_fun(line_msg.word[0]);
    return offset;
}
int asm_find_in_cmd(const char* word, LineRead line_msg)
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
            break;
    if(i >= 0 && i <= 2)
        return 4;
    else if(i >= 3 && i <= 14)
    {
        if(is_const(line_msg.word[2]))
            return 5;
        else
            return 4;
    }
    else if(i >= 15 && i <=17)
        return 3;
    else if(i >= 18 && i <= 25)
        return 6;
    else if(i == 26)
        return 2;
    else
        return 0;
}
int asm_find_in_fun(const char* word)
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
            return 2;
    return 0;
}
int find_in_sign(const char* word, struct Sign* head)
{
    struct Sign* cur;
    for(cur = head; cur != NULL; cur = cur -> next)
        if(strcmp(word, cur -> name) == 0)
            return cur -> offset;
    return -1;
}
unsigned char assemble_cmd(const char* word, LineRead line_msg)
{
    char cmd[39][6] =
    {
        "dtc",
        "ctd",
        "atp",
        "mov",
        "mov",
        "add",
        "add",
        "sub",
        "sub",
        "mul",
        "mul",
        "div",
        "div",
        "mod",
        "mod",
        "shl",
        "shl",
        "shr",
        "shr",
        "and",
        "and",
        "or",
        "or",
        "xor",
        "xor",
        "cmp",
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
    for(i = 0; i < 39; i++)
        if(strcmp(word, cmd[i]) == 0)
        {
            if(i >= 3 && i <= 26)
            {
                if(is_const(line_msg.word[2]))
                    return i + 1;
                else
                    return i + 2;
            }
            else
                return i + 1;
        }
    return 0;
}
unsigned char assemble_fun(const char* word)
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
            return i + 1;
    return 0;
}
unsigned char assemble_var(const char* word)
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
            return i + 1;
    return 0;
}
