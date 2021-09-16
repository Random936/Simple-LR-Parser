#include <stdio.h>
#include "include/lexer.h"

int main(int argc, char *argv[]) {

   Lexer *lexer = Lexer_init();
   Token *token = NULL;

   while ((token = Lexer_getToken(lexer))->type != TOK_EOF) {

   }

   return 0;
}
