# Calculator CLI — BUILD.md

## Requirements

- GCC (GNU C Compiler)
- C11 standard support

## Compilation

```sh
gcc -std=c11 -Wall -Wextra -pedantic calculator.c -o calculator
```

## Usage

```sh
./calculator
```

Follow the prompts: enter two integers and an operator (`+`, `-`, `*`, `/`, `%`).
Enter `q` at any number prompt to quit.

## Design

- Each arithmetic operation is implemented as a separate function taking two `int` parameters and returning an `int`.
- **Division by zero** is handled by printing an error message and returning `ERROR_DIV_ZERO` (a sentinel value near `INT_MAX`).
- The main loop repeats until the user enters `q`.
- Uses only basic C concepts: functions, return values, pass-by-value, and exit codes.
