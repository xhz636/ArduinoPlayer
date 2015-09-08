#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "apgc.h"
int main(int argc, char* argv[])
{
    int save_temp_file;
    int use_output_name;
    int apic_size;
    int i, j;
    char* input = NULL;
    char* output = NULL;
    char apas_name[256];
    save_temp_file = use_output_name = 0;
    for(i = 1; i < argc; i++)
    {
        if(argv[i][0] == '-')
        {
            for(j = 1; j < strlen(argv[i]); j++)
            {
                if(argv[i][j] == 's')
                    save_temp_file = 1;
                if(argv[i][j] == 'o')
                {
                    if(output == NULL)
                        use_output_name = 1;
                    else
                    {
                        puts("不能重复使用-o参数！");
                        return 0;
                    }
                }
            }
            if(use_output_name && output == NULL)
                if(i + 1 < argc)
                    output = argv[++i];
                else
                {
                    puts("-o参数后缺少输出文件名！");
                    return 0;
                }
        }
        else
            input = argv[i];
    }
    if(input == NULL)
    {
        puts("缺少源文件！");
        return 0;
    }
    if(compiler(input) == 0)
    {
        strcpy(apas_name, input);
        for(i = strlen(apas_name) - 1; i >= 0; i--)
        if(apas_name[i] == '.')
        {
            apas_name[i] == '\0';
            break;
        }
        strcat(apas_name, ".apas");
        if(assembler(apas_name) == 0)
        {
            printf("编译完成！\n");
            if(!save_temp_file)
                remove(apas_name);
        }
        else
            printf("汇编错误！\n");
    }
    else
        printf("编译错误！\n");
    return 0;
}
LineRead read_line(const char* line)
{
    LineRead line_msg;
    int i, j;
    int with_space = 0;
    for(i = 0, line_msg.count = 0; i < strlen(line); i++)
    {
        if(!isspace(line[i]))
        {
            for(j = 0; (!isspace(line[i]) || with_space) && i < strlen(line); j++)
            {
                line_msg.word[line_msg.count][j] = line[i++];
                if(line_msg.word[line_msg.count][j] == '\'')
                    with_space = !with_space;
                if(line_msg.word[line_msg.count][j] == '\"')
                    with_space = !with_space;
            }
            line_msg.word[line_msg.count][j] = '\0';
            line_msg.count++;
        }
    }
    return line_msg;
}
int is_const(const char* word)
{
    int i;
    if(word[0] == '\'' && word[strlen(word) - 1] == '\'')
    {
        if(strlen(word) == 3)
            return 1;
        if(word[1] == '\\' && (word[2] == 'x' || word[2] == 'X') && strlen(word) <= 6)
        {
            for(i = 2; i < strlen(word); i++)
                if(isxdigit(word[i]))
                    continue;
                else
                    return 0;
            return 1;
        }
        return 0;
    }
    else if(word[0] == '0' && (word[1] == 'x' || word[1] == 'X'))
    {
        for(i = 2; i < strlen(word); i++)
            if(isxdigit(word[i]))
                continue;
            else
                return 0;
        return 1;
    }
    else
    {
        for(i = 0; i < strlen(word); i++)
            if(isdigit(word[i]))
                continue;
            else
                return 0;
        return 1;
    }
}
short int read_const(const char* word)
{
    int i;
    short int num = 0;
    if(word[0] == '\'' && word[strlen(word) - 1] == '\'')
    {
        if(strlen(word) == 3)
            num = word[1];
        if(word[1] == '\\' && (word[2] == 'x' || word[2] == 'X') && strlen(word) <= 6)
            sscanf(word + 3, "%hx", &num);
    }
    else if(word[0] == '0' && (word[1] == 'x' || word[1] == 'X'))
        sscanf(word + 2, "%hx", &num);
    else
        sscanf(word, "%hd", &num);
    return num;
}
