#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "include/lexer.h"

Lexer *Lexer_init(char *src) {

   Lexer *lexer = malloc(sizeof(Lexer));
   lexer->src = src;
   lexer->crt = src[0];
   lexer->i = 0;

   return lexer;
}

void Lexer_error(Lexer *lexer) {
   printf("ERROR: Invalid token, %c\n", lexer->crt);
   exit(1);
}

void Lexer_adv(Lexer *lexer) {
   lexer->crt = lexer->src[++lexer->i];
}

Token *Lexer_getDigit(Lexer *lexer) {

   char *start = lexer->src + lexer->i;
   int size = 0;

   while (isdigit(lexer->crt)) {
      Lexer_adv(lexer);
      size++;
   }

   return Token_init(TOK_INT, start, size);
}

Token *Lexer_advToken(Lexer *lexer, enum tokenType type) {
   char *start = lexer->src + lexer->i;
   Lexer_adv(lexer);
   return Token_init(type, start, 1);
}

Token *Lexer_getToken(Lexer *lexer) {

   while (isspace(lexer->crt))
      Lexer_adv(lexer);

   if (isdigit(lexer->crt))
      return Lexer_getDigit(lexer);

   switch (lexer->crt) {
      case '+': return Lexer_advToken(lexer, TOK_ADD);
      case '-': return Lexer_advToken(lexer, TOK_SUB);
      case '*': return Lexer_advToken(lexer, TOK_MUL);
      case '/': return Lexer_advToken(lexer, TOK_DIV);
      case 0: return Token_init(TOK_EOF, NULL, 0);
   }

   Lexer_error(lexer);
   return NULL;
}
