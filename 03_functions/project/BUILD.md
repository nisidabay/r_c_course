# Calculator CLI — BUILD.md

## Overview

A simple integer calculator that reads two numbers and an operator (`+`, `-`,
`*`, `/`, `%`) and prints the result. Enter `q` at any number prompt to quit.
Demonstrates function definitions, pass-by-value, return values, division-by-
zero handling with a sentinel, and a `do-while` program loop with three
sequential `fgets` calls per iteration.

## Requirements

- GCC (GNU C Compiler) with C11 support
- Standard C library

## Build

```bash
gcc -std=c11 -Wall -Wextra -pedantic calculator.c -o calculator
```

## Usage

```bash
./calculator
```

```text
Enter number 1 (or 'q' to quit): 42
Enter number 2 (or 'q' to quit): 5
Enter operator (+, -, *, /, %): /
42 / 5 = 8

Enter number 1 (or 'q' to quit): 5
Enter number 2 (or 'q' to quit): 0
Enter operator (+, -, *, /, %): /
Error: division by zero

Enter number 1 (or 'q' to quit): q
Goodbye!
```

## Concepts Used

- Function definitions with `int` parameters and return values
- Pass-by-value semantics
- Division-by-zero detection with `ERROR_DIV_ZERO` sentinel
- `do-while` loop for the REPL (read-eval-print loop)
- Three `fgets` + `strtol` calls per iteration
- `consume_remaining` guard for each input
- Exit-controlled loop design (`do-while`)
