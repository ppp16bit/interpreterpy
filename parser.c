#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

static Token current_token;

static void next_token() {
    current_token = lexer_next_token();
}

static ASTNode *parse_expression();
static ASTNode *parse_term();
static ASTNode *parse_factor();

ASTNode *parse_program() {
    next_token();
    ASTNode *node = parse_expression();

    if (current_token.type != TOKEN_EOF) {
        fprintf(stderr, "expected EOF\n");
        exit(1);
    }

    return node;
}

static ASTNode *parse_expression() {
    ASTNode *node =parse_term();

    while (current_token.type == TOKEN_PLUS || current_token.type == TOKEN_MINUS) {
        ASTNode *op_node = malloc(sizeof(ASTNode));
        op_node->type = NODE_BINOP;
        op_node->ivalue = current_token.type;
        op_node->left = node;
        next_token();
        op_node->right = parse_term();
        node = op_node;
    }

    return node;
}

static ASTNode *parse_term() {
    ASTNode *node = parse_factor();

    while (current_token.type == TOKEN_MUL || current_token.type == TOKEN_DIV) {
        ASTNode *op_node = malloc(sizeof(ASTNode));
        op_node->type = NODE_BINOP;
        op_node->ivalue = current_token.type;
        op_node->left = node;
        next_token();
        op_node->right = parse_factor();
        node = op_node;
    }

    return node;
}

static ASTNode *parse_factor() {
    if (current_token.type == TOKEN_INT) {
        ASTNode *node = malloc(sizeof(ASTNode));
        node->type = NODE_INT;
        node->ivalue = current_token.ivalue;
        next_token();
        
        return node;
    }

    if (current_token.type == TOKEN_IDENT) {
        ASTNode *node = malloc(sizeof(ASTNode));
        node->type = NODE_IDENT;
        node->svalue = strdup(current_token.value);
        next_token();

        return node;
    }

    if (current_token.type == TOKEN_LPAREN) {
        next_token();
        ASTNode *node = parse_expression();

        if (current_token.type != TOKEN_RPAREN) {
            fprintf(stderr, "expected ')'\n");
            exit(1);
        }
        
        next_token();
        return node;
    }

    fprintf(stderr, "unexpected token\n");
    exit(1);
}

void astfree(ASTNode *node) {
    if (!node) return;

    astfree(node->left);
    astfree(node->right);

    if (node->type == NODE_IDENT && node->svalue) {
        free(node->svalue);
    }

    free(node);
}