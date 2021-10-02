#include <stdio.h>
#include "include/lexer.h"
#include "include/parser.h"

int main(int argc, char *argv[]) {

   char src[] = "10 + 3";

   Lexer *lexer = Lexer_init(src);
   Parser *parser = Parser_init(lexer);
   Parser_parse(parser);

   return 0;
}
