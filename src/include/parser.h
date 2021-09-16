#pragma once

#include "lexer.h"

typedef struct {
   Lexer *lexer;
   Token *crt;
   int state;
} Parser;

typedef struct {
   int state;
   char action;
} TableNode;
