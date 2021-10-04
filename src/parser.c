#include <stdio.h>
#include <stdlib.h>

#include "include/parser.h"


#define PTN(A, S) \
   {.action=A, .state=S}

void error(char *msg) {
   fprintf(stderr, "ERROR: %s\n", msg);
   exit(1);
}

int itemSetLength[ITEMSET_NUM] = {1, 3, 3, 1, 3, 3, 1, 1};

/*
void TableNode_print(TableNode *node) {
   printf(
         "<TableNode action=%c state=%d>\n",
         node->action,
         node->state
      );
}
*/

TableNode parseTable[STATE_NUM][TOKENTYPE_LEN + NONTERMINAL_NUM] = {
   { PTN('i', 0),  PTN('i', 0), PTN('i', 0), PTN('i', 0),  PTN('s', 4),  PTN('i', 0),   PTN(0, 1),   PTN(0, 2),   PTN(0, 3) },
   { PTN('s', 5),  PTN('s', 6), PTN('i', 0), PTN('i', 0),  PTN('i', 0),  PTN('a', 0), PTN('i', 0), PTN('i', 0), PTN('i', 0) },
   { PTN('r', 3),  PTN('r', 3), PTN('s', 7), PTN('s', 8),  PTN('i', 0),  PTN('r', 3), PTN('i', 0), PTN('i', 0), PTN('i', 0) },
   { PTN('r', 6),  PTN('r', 6), PTN('r', 6), PTN('r', 6),  PTN('i', 0),  PTN('r', 6), PTN('i', 0), PTN('i', 0), PTN('i', 0) },
   { PTN('r', 7),  PTN('r', 7), PTN('r', 7), PTN('r', 7),  PTN('i', 0),  PTN('r', 7), PTN('i', 0), PTN('i', 0), PTN('i', 0) },
   { PTN('i', 0),  PTN('i', 0), PTN('i', 0), PTN('i', 0),  PTN('s', 4),  PTN('i', 0), PTN('i', 0),   PTN(0, 9),   PTN(0, 3) },
   { PTN('i', 0),  PTN('i', 0), PTN('i', 0), PTN('i', 0),  PTN('s', 4),  PTN('i', 0), PTN('i', 0),  PTN(0, 10),   PTN(0, 3) },
   { PTN('i', 0),  PTN('i', 0), PTN('i', 0), PTN('i', 0),  PTN('s', 4),  PTN('i', 0), PTN('i', 0), PTN('i', 0),  PTN(0, 11) },
   { PTN('i', 0),  PTN('i', 0), PTN('i', 0), PTN('i', 0),  PTN('s', 4),  PTN('i', 0), PTN('i', 0), PTN('i', 0),  PTN(0, 12) },
   { PTN('r', 1),  PTN('r', 1), PTN('s', 7), PTN('s', 8),  PTN('i', 0),  PTN('r', 1), PTN('i', 0), PTN('i', 0), PTN('i', 0) },
   { PTN('r', 2),  PTN('r', 2), PTN('s', 7), PTN('s', 8),  PTN('i', 0),  PTN('r', 2), PTN('i', 0), PTN('i', 0), PTN('i', 0) },
   { PTN('r', 4),  PTN('r', 4), PTN('r', 4), PTN('r', 4),  PTN('i', 0),  PTN('r', 4), PTN('i', 0), PTN('i', 0), PTN('i', 0) },
   { PTN('r', 5),  PTN('r', 5), PTN('r', 5), PTN('r', 5),  PTN('i', 0),  PTN('r', 5), PTN('i', 0), PTN('i', 0), PTN('i', 0) },
};

Parser *Parser_init(Lexer *lexer) {

   Parser *parser = malloc(sizeof(Parser));
   parser->lexer = lexer;
   parser->crt = Lexer_getToken(lexer);
   parser->stack = Stack_init(STACK_SIZE);
   Stack_push(parser->stack, StackNode_init(0, START, NULL));

   return parser;
}

TableNode Parser_tableLookup(int state, int type) {
   return parseTable[state][type];
}

void Parser_adv(Parser *parser) {
   parser->crt = Lexer_getToken(parser->lexer);
}

void Parser_parse(Parser *parser) {

   while (1) {

      TableNode rule = Parser_tableLookup(Stack_at(parser->stack, 0)->state, parser->crt->type);

      //TableNode_print(&rule);

      switch (rule.action) {
         case 0: Stack_at(parser->stack, 0)->state = rule.state;
         case 'i': 
              printf(
                    "INFO: Last rule index: (%d, %d)\n",
                    parser->crt->type,
                    Stack_at(parser->stack, 0)->state
                 );
              error("Unexpected token.");
         case 's': Parser_shift(parser, rule.state); break;
         case 'r': Parser_reduce(parser, rule.state); break;
         case 'a': return;
      }

   }
}

void Parser_reduce(Parser *parser, int itemset) {

   enum dataType type;
   void *value = NULL;

   switch (itemset) {
      case 1: // E -> E + T
         type = AST_EXPR;
         value = Expr_init(Stack_valAt(parser->stack, -2), '+', Stack_valAt(parser->stack, 0));
         break;
      case 2: // E -> E - T
         type = AST_EXPR;
         value = Expr_init(Stack_valAt(parser->stack, -2), '-', Stack_valAt(parser->stack, 0));
         break;
      case 3: // E -> T
         type = AST_EXPR;
         value = Expr_init(NULL, 0, Stack_valAt(parser->stack, 0));
         break;
      case 4: // T -> T * F
         type = AST_TERM;
         value = Term_init(Stack_valAt(parser->stack, -2), '*', Stack_valAt(parser->stack, 0));
         break;
      case 5: // T -> T / F
         type = AST_TERM;
         value = Term_init(Stack_valAt(parser->stack, -2), '/', Stack_valAt(parser->stack, 0));
         break;
      case 6: // T -> F
         type = AST_TERM;
         value = Term_init(NULL, 0, Stack_valAt(parser->stack, 0));
         break;
      case 7: // F -> id
         type = AST_FACT;
         value = Fact_init(atoi(((Token *)Stack_valAt(parser->stack, 0))->start));
         break;
   }

   StackNode *new = StackNode_init(0, type, value);
   Stack_rem(parser->stack, itemSetLength[itemset]);
   new->state = Parser_tableLookup(Stack_at(parser->stack, 0)->state, TOKENTYPE_LEN + (type - AST_EXPR)).state;
   Stack_push(parser->stack, new);
}

void Parser_shift(Parser *parser, int state) {
   Stack_push(parser->stack, StackNode_init(state, TOKEN, parser->crt));
   Parser_adv(parser);
}
