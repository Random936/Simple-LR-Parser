#pragma once

#include "lexer.h"
#include "ast.h"
#include "stack.h"

#define NONTERMINAL_NUM 3
#define STATE_NUM 13
#define ITEMSET_NUM 8
#define STACK_SIZE 1024

typedef struct {
   int state;
   char action;
} TableNode;

typedef struct {
   Lexer *lexer;
   Token *crt;
   Stack *stack;
} Parser;

TableNode Parser_tableLookup(int state, int type);
Parser *Parser_init(Lexer *lexer);
void Parser_parse(Parser *parser);
void Parser_reduce(Parser *parser, int itemset);
void Parser_shift(Parser *parser, int state);
