#include <stdio.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/eval.h"

int main(int argc, char *argv[]) {

   Lexer *lexer = Lexer_init(argv[1]);
   Parser *parser = Parser_init(lexer);
   Parser_parse(parser);
   Expr *expr = Stack_at(parser->stack, 0)->value;
   int value = Expr_eval(expr);
   printf("%d\n", value);

   return 0;
}
