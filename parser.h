#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"

typedef enum {
    NODE_BINOP, NODE_ASSIGN, NODE_IF,
    NODE_WHILE, NODE_INT, NODE_IDENT
} NodeType;

typedef struct ASTNode {
    NodeType type;
    struct ASTNode *left;
    struct ASTNode *right;
    char *svalue;
    int ivalue;
} ASTNode;

ASTNode *parse_program();
void ast_free(ASTNode *node);

#endif