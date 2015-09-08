#ifndef ASSEMBLER_H
#define ASSEMBLER_H
struct Sign
{
    char name[256];
    int offset;
    struct Sign* next;
};
int assembler(const char* apas_name);
struct Sign* read_sign(FILE* apas);
int read_offset(LineRead line_msg);
int asm_find_in_cmd(const char* word, LineRead line_msg);
int asm_find_in_fun(const char* word);
int asm_find_in_sign(const char* word, struct Sign* head);
unsigned char assemble_cmd(const char* word, LineRead line_msg);
unsigned char assemble_fun(const char* word);
unsigned char assemble_var(const char* word);
#endif
