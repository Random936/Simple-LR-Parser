#pragma once

#include "token.h"

enum ASTType {
   AST_EXPR,
   AST_TERM,
   AST_FACT
};

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

typedef struct {
   enum ASTType type;
   void *node;
} ASTNode;
ASTNode *AST_init(enum ASTType type, void *node);
void AST_print(ASTNode *ast);
