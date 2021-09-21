#pragma once

typedef struct {
   void *left;
   char op;
   void *right;
} ASTNode;

typedef struct {
   int val;
} Literal;
