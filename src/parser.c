#include <stdio.h>
#include <stdlib.h>

#include "include/parser.h"

#define PTN(A, S) \
   {.action=A, .state=S}


StackNode *StackNode_init(enum dataType type, void *data) {

   StackNode *node = malloc(sizeof(StackNode));
   node->type = type;

   switch (type) {
      case TOKEN:
         node->token = data;
      case STATE:
         node->state = data;
      case AST_NODE:
         node->node = data;
   }

   return node;
}
   
StackNode *Stack_pop(StackNode **head) {
   StackNode *popped = *head;
   *head = (*head)->next;
   return popped;
}

void Stack_push(StackNode **head, StackNode *node) {
   node->next = *head;
   *head = node;
}

TableNode parseTable[STATE_NUM][TOKENTYPE_LEN + NONTERMINAL_NUM] = {
   { {0}, {0}, {0}, {0}, PTN('s', 4), {0}, PTN(0, 1), PTN(0, 2), PTN(0, 3) },
   { PTN('s', 5), PTN('s', 6), {0}, {0}, {0}, PTN('a', 0), {0}, {0}, {0} },
   { {0}, {0}, PTN('s', 7), PTN('s', 8), {0}, {0}, {0}, {0}, {0} },
   { PTN('r', 3), PTN('r', 3), PTN('r', 3), PTN('r', 3), {0}, PTN('r', 3), {0}, {0}, {0} },
   { PTN('r', 4), PTN('r', 4), PTN('r', 4), PTN('r', 4), {0}, PTN('r', 4), {0}, {0}, {0} },
   { {0}, {0}, {0}, {0}, PTN('s', 4), {0}, {0}, PTN(0, 9), PTN(0, 3) },
   { {0}, {0}, {0}, {0}, PTN('s', 4), {0}, {0}, PTN(0, 10), PTN(0, 3) },
   { {0}, {0}, {0}, {0}, PTN('s', 4), {0}, {0}, {0}, PTN(0, 11) },
   { {0}, {0}, {0}, {0}, PTN('s', 4), {0}, {0}, {0}, PTN(0, 12) },
   { {0}, {0}, PTN('s', 7), PTN('s', 8), {0}, {0}, {0}, {0}, {0} },
   { {0}, {0}, PTN('s', 7), PTN('s', 8), {0}, {0}, {0}, {0}, {0} },
   { PTN('r', 11), PTN('r', 11), {0}, {0}, PTN('r', 11), PTN('r', 11), {0}, {0}, {0} },
   { PTN('r', 12), PTN('r', 12), {0}, {0}, {0}, {0}, {0}, {0}, {0} },
};

TableNode Parser_tableLookup(int state, Token *token) {
   return parseTable[state][token->type];
}

void Parser_parse(Parser *parser) {
}

void Parser_reduce(Parser *parser) {
}

void Parser_shift(Parser *parser) {
}

