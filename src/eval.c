#include <stdio.h>
#include <stdlib.h>

#include "include/eval.h"

int Expr_eval(Expr *expr) {

   if (expr->right == NULL)
      printf("EXPR: Right is null\n");

   int b = Term_eval(expr->right);

   if (expr->left != NULL) {
      int a = Expr_eval(expr->left);
      switch (expr->op) {
         case '+': return a + b;
         case '-': return a - b;
      }
   }

   return b;
}

int Term_eval(Term *term) {

   if (term->right == NULL)
      printf("TERM: Right is null\n");

   int b = Fact_eval(term->right);

   if (term->left != NULL) {
      int a = Term_eval(term);
      switch (term->op) {
         case '+': return a + b;
         case '-': return a - b;
      }
   }

   return b;
}

int Fact_eval(Fact *fact) {
   if (fact == NULL)
      printf("Fact is null\n");

   return fact->val;
}
