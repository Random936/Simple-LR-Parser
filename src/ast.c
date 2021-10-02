#include <stdlib.h>

#include "include/ast.h"

ASTNode *AST_init(void *left, char op, void *right) {
   ASTNode *node = malloc(sizeof(ASTNode));
   node->left = left;
   node->op = op;
   node->right = right;

   return node;
}

Literal *Literal_init(int val) {
   Literal *literal = malloc(sizeof(Literal));
   literal->val = val;
   return literal;
}
