#include <stdio.h>
#include <stdlib.h>

#include "include/stack.h"

char *dataTypeLookup[] = {
   "START",
   "TOKEN",
   "AST_NODE"
};


StackNode *StackNode_init(int state, enum dataType type, void *value) {

   StackNode *node = malloc(sizeof(StackNode));
   node->type = type;
   node->state = state;
   node->value = value;

   return node;
}

void StackNode_print(StackNode *node) {
   if (node == NULL)
      return;

   printf(
         "<StackNode type=%s state=%d>\n",
         dataTypeLookup[node->type],
         node->state
      );
}


Stack *Stack_init(int size) {

   Stack *stack = malloc(sizeof(Stack));
   stack->nodes = malloc(sizeof(StackNode *) * size);
   stack->sp = 0;

   return stack;
}

StackNode *Stack_at(Stack *stack, int offset) {
   return stack->nodes[stack->sp + offset];
}
   
void Stack_rem(Stack *stack, int num) {
   stack->sp -= num;
}

void Stack_push(Stack *stack, StackNode *node) {
   stack->nodes[++stack->sp] = node;
}

void Stack_print(Stack *stack) {
   for (int i = 0; i < stack->sp; i++) {
      StackNode_print(stack->nodes[i]);
   }
}
