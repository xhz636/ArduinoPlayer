#ifndef COMPILER_H
#define COMPILER_H
#include "apgc.h"
struct Variable
{
    char name[256];
    char type[16];
    int index;
    struct Variable* next;
};
int compiler(const char* apsc_name);
struct Variable* read_variable(FILE* apsc);
struct Variable* find_in_variable(const char* word, struct Variable* head);
int find_in_cmd(const char* word);
int find_in_fun(const char* word);
int find_in_var(const char* word);
void compile_cmd(LineRead line_msg, struct Variable* head, int cmd_flag, FILE* apas);
void compile_fun(LineRead line_msg, struct Variable* head, int fun_flag, FILE* apas);
char* compile_var(const char* word, struct Variable* head, int which, FILE* apas);
void write_string(LineRead line_msg, struct Variable* head, FILE* apas);
#endif
