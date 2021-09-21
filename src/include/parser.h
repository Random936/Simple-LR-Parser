#pragma once

#include "lexer.h"
#include "ast.h"

#define NONTERMINAL_NUM 3
#define STATE_NUM 13

enum dataType {
   TOKEN,
   STATE,
   AST_NODE
};

typedef struct {
   int state;
   char action;
} TableNode;

typedef struct StackNode_s StackNode;
struct StackNode_s {
   enum dataType type;
   union {
      Token *token;
      TableNode *state;
      ASTNode *node;
   };
   StackNode *next;
};
StackNode *StackNode_init(enum dataType type, void *data);
StackNode *Stack_pop(StackNode **head);
void Stack_push(StackNode **head, StackNode *node);

typedef struct {
   Lexer *lexer;
   Token *crt;
   StackNode *stack;
} Parser;

TableNode Parser_tableLookup(int state, Token *token);
void Parser_parse(Parser *parser);
void Parser_reduce(Parser *parser);
void Parser_shift(Parser *parser);
