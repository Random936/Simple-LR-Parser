#include <stdio.h>
#include <stdlib.h>

#include "include/ast.h"

Fact *Fact_init(int val) {
   Fact *fact = malloc(sizeof(Fact));
   fact->val = val;

   return fact;
}

Expr *Expr_init(Expr *left, char op, Term *right) {
   Expr *expr = malloc(sizeof(Expr));
   expr->left = left;
   expr->op = op;
   expr->right = right;

   return expr;
}

Term *Term_init(Term *left, char op, Fact *right) {
   Term *term = malloc(sizeof(Term));
   term->left = left;
   term->op = op;
   term->right = right;

   return term;
}
