#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "parser.h"

void interpreter_init();
int interpret(ASTNode *node);
void interpreter_cleanup();

#endif