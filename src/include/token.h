#pragma once
#define TOKENTYPE_LEN TOK_EOF - TOK_ADD + 1

enum tokenType {
   TOK_ADD = 0,
   TOK_SUB,
   TOK_MUL,
   TOK_DIV,
   TOK_INT,
   TOK_EOF
};

typedef struct {
   enum tokenType type;
   char *start;
   int size;
} Token;

Token *Token_init(enum tokenType type, char *start, int size);
void Token_print(Token *token);
