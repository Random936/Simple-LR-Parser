#include <stdio.h>
#include <stdlib.h>

#include "include/stack.h"

StackNode *StackNode_init(int state, enum dataType type, void *value) {

   StackNode *node = malloc(sizeof(StackNode));
   node->type = type;
   node->state = state;
   node->value = value;

   return node;
}

Stack *Stack_init(int size) {

   Stack *stack = malloc(sizeof(Stack));
   stack->nodes = malloc(sizeof(StackNode *) * size);
   stack->sp = -1;

   return stack;
}

StackNode *Stack_at(Stack *stack, int offset) {
   return stack->nodes[stack->sp + offset];
}

void *Stack_valAt(Stack *stack, int offset) {
   return stack->nodes[stack->sp + offset]->value;
}
   
void Stack_rem(Stack *stack, int num) {
   stack->sp -= num;
}

void Stack_push(Stack *stack, StackNode *node) {
   stack->nodes[++stack->sp] = node;
}
