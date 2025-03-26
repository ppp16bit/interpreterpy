#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

static char *input;
static size_t pos;
static size_t input_length;
static int line = 1;

const char *keywords[] = {"if", "while", NULL};

void lexer_init(char *text) {
  input = text;
  pos = 0;
  input_length = strlen(input);
}

static void skip_whitespace() {
  while (pos < input_length && isspace(input[pos])) {
    if (input[pos] == '\n') line++;
    pos++;
  }
}

Token lexer_next_token() {
    skip_whitespace();

    if (pos >= input_length) {
        return (Token){TOKEN_EOF, NULL, 0};
    }

    char current = input[pos];

    if (isdigit(current)) { // numbers
        int val = 0;

        while (pos < input_length && isdigit(input[pos])) {
            val = val * 10 + (input[pos] - '0');
            pos++;
        }
        return (Token){TOKEN_INT, NULL, val};
    }

    if (isalpha(current) || current == '_') { // identifiers n keywords
        char *start = input + pos;

        while (pos < input_length && (isalnum(input[pos]) || input[pos] == '_')) {
            pos++;
        }

        size_t len = input + pos - start;
        char *ident = mystrndup(start, len); // strndup implementation applied

        for (const char **keyword = keywords; *keyword; keyword++) { // check kw
          if (strcmp(ident, *keyword) == 0) {
            free(ident);

            if (strcmp(*keyword, "if") == 0) return (Token){TOKEN_IF, NULL, 0};
            if (strcmp(*keyword, "while") == 0) return (Token){TOKEN_WHILE, NULL, 0};
          }
        }
        return (Token){TOKEN_IDENT, ident, 0};
    }

    // op n punctuation
    switch (current) {
      case '+': pos++; return (Token){TOKEN_PLUS, NULL, 0};
      case '-': pos++; return (Token){TOKEN_MINUS, NULL, 0};
      case '*': pos++; return (Token){TOKEN_MUL, NULL, 0};
      case '/': pos++; return (Token){TOKEN_DIV, NULL, 0};
      case '(': pos++; return (Token){TOKEN_LPAREN, NULL, 0};
      case ')': pos++; return (Token){TOKEN_RPAREN, NULL, 0};
      case ':': pos++; return (Token){TOKEN_COLON, NULL, 0};
      case '=':
          if (pos + 1 < input_length && input[pos + 1] == '=') {
            pos += 2; return (Token){TOKEN_EE, NULL, 0};
          }
          pos++;
          return (Token){TOKEN_EQ, NULL, 0};
      case '<':
          if (pos + 1 < input_length && input[pos + 1] == '=') {
            pos += 2; return (Token){TOKEN_LE, NULL, 0};
          }
          pos++; return (Token){TOKEN_LT, NULL, 0};
      case '>':
          if (pos + 1 < input_length && input[pos + 1] == '=') {
            pos += 2; return (Token){TOKEN_GE, NULL, 0};
          }
          pos++; return (Token){TOKEN_GT, NULL, 0};
      case '!':
          if (pos + 1 < input_length && input[pos + 1] == '=') {
            pos += 2; return (Token){TOKEN_NE, NULL, 0};
          }
          break;
      case '\n':
          pos++; return (Token){TOKEN_NEWLINE, NULL, 0};
    }

    fprintf(stderr, "unexpected char '%c' at line %d\n", current, line);
    exit(1);
}