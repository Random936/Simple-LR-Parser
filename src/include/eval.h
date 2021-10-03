#pragma once

#include "ast.h"

int Expr_eval(Expr *expr);
int Term_eval(Term *term);
int Fact_eval(Fact *fact);
