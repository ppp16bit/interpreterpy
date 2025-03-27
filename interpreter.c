#include "interpreter.h"
#include "lexer.h"
#include "parser.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char *name;
    int value;
} Variable;

static Variable *variables;
static size_t var_count;

void interpreter_init() {
    variables = NULL;
    var_count = 0;
}

static int eval(ASTNode *node) {
    switch (node->type) {
        case NODE_INT:
            return node->ivalue;
        case NODE_IDENT: {
            for (size_t i = 0; i < var_count; i++) {
                if (strcmp(variables[i].name, node->svalue) == 0) {
                    return variables[i].value;
                }
            }
            fprintf(stderr, "undefined var '%s'\n", node->svalue);
            exit(1);
        }

        case NODE_BINOP: {
            int left = eval(node->left);
            int right = eval(node->right);

            switch (node->ivalue) {
                case TOKEN_PLUS: return left + right;
                case TOKEN_MINUS: return left - right;
                case TOKEN_MUL: return left * right;
                case TOKEN_DIV: return left / right;
                default:
                    fprintf(stderr, "unknow operator\n");
                    exit(1);
            }
        }

        case NODE_ASSIGN: {
            int value = eval(node->left);

            for (size_t i = 0; i < var_count; i++) {
                if (strcmp(variables[i].name, node->svalue) == 0) {
                    variables[i].value = value;
                    return value;
                }
            }

            variables = realloc(variables, (var_count + 1) * sizeof(Variable));
            
            variables[var_count].name = strdup(node->svalue);
            variables[var_count].value = value;
            var_count++;
            
            return value;
        }

        default:
            fprintf(stderr, "unknow node type\n");
            exit(1);
    }
}

int interpret(ASTNode *node) {
    return eval(node);
}

void interpreter_cleanup() {
    for (size_t i = 0; i < var_count; i++) {
        free(variables[i].name);
    }

    free(variables);
    var_count = 0;
}