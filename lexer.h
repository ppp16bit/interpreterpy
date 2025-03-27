#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_INT, TOKEN_IDENT, TOKEN_KEYWORD, TOKEN_PLUS, TOKEN_MINUS,
    TOKEN_MUL, TOKEN_DIV, TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_COLON, 
    TOKEN_EQ, TOKEN_IF, TOKEN_WHILE, TOKEN_EOF, TOKEN_NEWLINE,
    TOKEN_LT, TOKEN_GT, TOKEN_LE, TOKEN_GE, TOKEN_NE, TOKEN_EE
} TokenType;

typedef struct {
    TokenType type;
    char *value;
    int ivalue;
} Token;

void lexer_init(char *input);
Token lexer_next_token();
void lexer_cleanup();

#endif