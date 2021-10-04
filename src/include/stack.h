#pragma once

#include "token.h"
#include "ast.h"

enum dataType {
   START = 0,
   TOKEN,
   AST_EXPR = 2,
   AST_TERM,
   AST_FACT
};

typedef struct {
   enum dataType type;
   int state;
   void *value;
} StackNode;

typedef struct {
   StackNode **nodes;
   int sp;
} Stack;

StackNode *StackNode_init(int state, enum dataType type, void *value);
void StackNode_print(StackNode *node);

Stack *Stack_init(int size);
StackNode *Stack_at(Stack *stack, int offset);
void *Stack_valAt(Stack *stack, int offset);
void Stack_rem(Stack *stack, int num);
void Stack_push(Stack *stack, StackNode *node);
