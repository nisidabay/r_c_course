# Calculator — BUILD.md

## Overview

A simple integer calculator that reads two numbers and an operator (`+`, `-`,
`*`, `/`, `%`) and prints the result. Demonstrates function definitions,
parameters, return values, and input validation via `strtol` — core concepts
from group 03.

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

Enter the first number, an operator, and the second number when prompted.
Type `q` at any prompt to quit:

```text
=== Integer Calculator ===
Enter 'q' or press Ctrl+D at any prompt to quit.

Enter a number: 10
Enter operator (+ - * / %): *
Enter a number: 3
10 * 3 = 30

Enter a number: 100
Enter operator (+ - * / %): /
Enter a number: 7
100 / 7 = 14

Enter a number: q

Exiting calculator.
```

## Concepts Used

- Function definition and calls (`add`, `subtract`, `multiply`, `divide`, `modulo`)
- Parameters and return values
- `strtol` for safe integer parsing with full error detection
- `fgets` + `strcspn` for safe input
- `strchr` for operator validation
- Edge case handling: division by zero, `INT_MIN / -1` overflow
