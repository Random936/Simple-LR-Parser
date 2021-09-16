#pragma once
#define TOKENTYPE_LEN TOK_EOF - TOK_INT

enum tokenType {
   TOK_INT = 0,
   TOK_ADD,
   TOK_SUB,
   TOK_MUL,
   TOK_DIV,
   TOK_EOF
};

typedef struct {
   enum tokenType type;
   char *start;
   int size;
} Token;

Token *Token_init(enum tokenType type, char *start, int size);
void Token_print(Token *token);
