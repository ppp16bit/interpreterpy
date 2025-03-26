#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "parser.h"

void interpreter_init();
int interpet(ASTNode *node);
void interpreter_cleanup();

#endif