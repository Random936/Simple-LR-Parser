#include <stdio.h>
#include <stdlib.h>

#include "include/token.h"

char *tokenTypeLookup[] = {
   "TOK_INT",
   "TOK_ADD",
   "TOK_SUB",
   "TOK_MUL",
   "TOK_DIV",
   "TOK_EOF"
};

Token *Token_init(enum tokenType type, char *start, int size) {
   Token *token = malloc(sizeof(Token));
   token->type = type;
   token->start = start;
   token->size = size;

   return token;
}

void Token_print(Token *token) {
   printf(
      "<Token type=%s value=%.*s>\n",
      tokenTypeLookup[token->type],
      token->size,
      token->start
   );
}
