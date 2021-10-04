#pragma once

#include "token.h"

typedef struct {
   int val;
} Fact;
Fact *Fact_init(int val);

typedef struct Term_s Term;
struct Term_s {
   Term *left;
   char op;
   Fact *right;
};
Term *Term_init(Term *left, char op, Fact *right);

typedef struct Expr_s Expr;
struct Expr_s {
   Expr *left;
   char op;
   Term *right;
};
Expr *Expr_init(Expr *left, char op, Term *right);
