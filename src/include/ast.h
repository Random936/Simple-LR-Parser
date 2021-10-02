#pragma once

typedef struct {
   void *left;
   char op;
   void *right;
} ASTNode;
ASTNode *AST_init(void *left, char op, void *right);

typedef struct {
   int val;
} Literal;
Literal *Literal_init(int val);
