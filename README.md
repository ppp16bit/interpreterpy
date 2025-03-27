# interpreterpy

This repository contains a simple interpreter implemented in C. It is designed to perform basic arithmetic and variable assignment operations. The code is organized into separate modules for lexing, parsing, and interpretation.

## Features

- **Lexical Analysis:** Tokenizes input strings into numbers, identifiers, operators, and punctuation.
- **Parsing:** Builds an abstract syntax tree (AST) from arithmetic expressions and assignments.
- **Interpretation:** Evaluates the AST to compute arithmetic expressions and manage variables.

## Prerequisites

- A C compiler (e.g., gcc)
- Make

## Building the Project

To build the interpreter, run the following command in the project directory:

```bash
make
```

This command compiles the source files and produces an executable.

## Running the Interpreter

An example usage is provided in `main.c`. After building the project, run the executable:

```bash
./interpreterpy
```

The sample code in `main.c` demonstrates parsing and evaluating a simple code snippet:

```c
// example in main.c
char *code = "x = 10\ny = x + 5";
lexer_init(code);
ASTNode *ast = parse_program();
lexer_cleanup();
interpreter_init();
int result = interpret(ast);
printf("result: %d\n", result);
interpreter_cleanup();
ast_free(ast);
```

This example assigns a value to variable `x`, computes a new value for `y` by adding 5 to `x`, and then prints the result.