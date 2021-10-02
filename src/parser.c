#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "include/parser.h"


#define PTN(A, S) \
   {.action=A, .state=S}

void error(char *msg) {
   fprintf(stderr, "ERROR: %s\n", msg);
   exit(1);
}

int itemSetLength[ITEMSET_NUM] = {1, 3, 3, 1, 3, 3, 1, 1};

void TableNode_print(TableNode *node) {
   printf(
         "<TableNode action=%c state=%d>\n",
         node->action,
         node->state
      );
}

TableNode parseTable[STATE_NUM][TOKENTYPE_LEN + NONTERMINAL_NUM] = {
   {          {0},          {0},         {0},         {0},  PTN('s', 4),          {0}, PTN(0, 1),  PTN(0, 2),  PTN(0, 3) },
   {  PTN('s', 5),  PTN('s', 6),         {0},         {0},          {0},  PTN('a', 0),       {0},        {0},        {0} },
   {          {0},          {0}, PTN('s', 7), PTN('s', 8),          {0},          {0},       {0},        {0},        {0} },
   {  PTN('r', 3),  PTN('r', 3), PTN('r', 3), PTN('r', 3),          {0},  PTN('r', 3),       {0},        {0},        {0} },
   {  PTN('r', 4),  PTN('r', 4), PTN('r', 4), PTN('r', 4),          {0},  PTN('r', 4),       {0},        {0},        {0} },
   {          {0},          {0},         {0},         {0},  PTN('s', 4),          {0},       {0},  PTN(0, 9),  PTN(0, 3) },
   {          {0},          {0},         {0},         {0},  PTN('s', 4),          {0},       {0}, PTN(0, 10),  PTN(0, 3) },
   {          {0},          {0},         {0},         {0},  PTN('s', 4),          {0},       {0},        {0}, PTN(0, 11) },
   {          {0},          {0},         {0},         {0},  PTN('s', 4),          {0},       {0},        {0}, PTN(0, 12) },
   {          {0},          {0}, PTN('s', 7), PTN('s', 8),          {0},          {0},       {0},        {0},        {0} },
   {          {0},          {0}, PTN('s', 7), PTN('s', 8),          {0},          {0},       {0},        {0},        {0} },
   { PTN('r', 11), PTN('r', 11),         {0},         {0}, PTN('r', 11), PTN('r', 11),       {0},        {0},        {0} },
   { PTN('r', 12), PTN('r', 12),         {0},         {0},          {0},          {0},       {0},        {0},        {0} },
};

Parser *Parser_init(Lexer *lexer) {

   Parser *parser = malloc(sizeof(Parser));
   parser->lexer = lexer;
   parser->crt = Lexer_getToken(lexer);
   parser->stack = Stack_init(STACK_SIZE);
   Stack_push(parser->stack, StackNode_init(0, START, NULL));

   return parser;
}

TableNode Parser_tableLookup(int state, Token *token) {
   return parseTable[state][token->type];
}

void Parser_adv(Parser *parser) {
   parser->crt = Lexer_getToken(parser->lexer);
}

void Parser_parse(Parser *parser) {

   while (1) {

      TableNode rule = Parser_tableLookup(Stack_at(parser->stack, 0)->state, parser->crt);

      TableNode_print(&rule);

      Stack_print(parser->stack);

      switch (rule.action) {
         case 's': Parser_shift(parser, rule.state); break;
         case 'r': Parser_reduce(parser, rule.state); break;
         case 'a': return;
      }

   }
}

void Parser_reduce(Parser *parser, int itemset) {

   void *value = NULL;

   switch (itemset) {
      case 1: // E' -> E
         AST_init(Stack_at(parser->stack, 0), 0, NULL); break;
      case 2: // E -> E + T
         value = AST_init(Stack_at(parser->stack, -2), '+', Stack_at(parser->stack, 0)); break;
      case 3: // E -> E - T
         value = AST_init(Stack_at(parser->stack, -2), '-', Stack_at(parser->stack, 0)); break;
      case 4: // E -> T
         AST_init(Stack_at(parser->stack, 0), 0, NULL); break;
         break;
      case 5: // E -> T * F
         value = AST_init(Stack_at(parser->stack, -2), '*', Stack_at(parser->stack, 0)); break;
      case 6: // E -> T / F
         value = AST_init(Stack_at(parser->stack, -2), '/', Stack_at(parser->stack, 0)); break;
      case 7: // T -> F
         value = AST_init(Stack_at(parser->stack, 0), 0, NULL); break;
         break;
      case 8: // F -> id
         value = Literal_init(*(int *)Stack_at(parser->stack, 0)->value); break;
         break;
   }

   StackNode *new = StackNode_init(itemset, AST_NODE, value);
   Stack_rem(parser->stack, itemSetLength[itemset]);
   Stack_push(parser->stack, new);
}

void Parser_shift(Parser *parser, int state) {
   Stack_push(parser->stack, StackNode_init(state, TOKEN, parser->crt));
}
