#include <stdio.h>
#include <stdlib.h>

#include "include/eval.h"

int Expr_eval(Expr *expr) {


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

   int b = Fact_eval(term->right);

   if (term->left != NULL) {
      int a = Term_eval(term->left);
      switch (term->op) {
         case '*': return a * b;
         case '/': return a / b;
      }
   }

   return b;
}

int Fact_eval(Fact *fact) {
   return fact->val;
}
