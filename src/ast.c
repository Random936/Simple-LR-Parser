#include <stdio.h>
#include <stdlib.h>

#include "include/ast.h"

char *ASTTypeLookup[] = {
   "AST_EXPR",
   "AST_TERM",
   "AST_FACT"
};

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

ASTNode *AST_init(enum ASTType type, void *node) {
   ASTNode *ast = malloc(sizeof(ASTNode));
   ast->type = type;
   ast->node = node;
   
   return ast;
}

void AST_print(ASTNode *ast) {
   printf(
         "<ASTNode type=%s node=%p>\n",
         ASTTypeLookup[ast->type],
         ast->node
      );
}
