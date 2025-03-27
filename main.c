#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include <stdio.h>

int main(void) {
    // example
    char *code = "x = 10\ny = x + 5";

    lexer_init(code);
    ASTNode *ast = parse_program();
    lexer_cleanup();

    interpreter_init();
    int result = interpret(ast);
    printf("result: %d\n", result);

    interpreter_cleanup();
    ast_free(ast);

    return 0;
}