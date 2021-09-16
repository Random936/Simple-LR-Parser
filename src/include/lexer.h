#pragma once
#include "token.h"

typedef struct {
   char *src;
   char crt;
   int i;
} Lexer;

Lexer *Lexer_init(char *src);
void Lexer_adv(Lexer *lexer);
Token *Lexer_getDigit(Lexer *lexer);
Token *Lexer_advToken(Lexer *lexer, enum tokenType type);
Token *Lexer_getToken(Lexer *lexer);
