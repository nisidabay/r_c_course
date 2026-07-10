# BUILD.md — Number Guessing Game

## Requirements

- **Compiler**: GCC (GNU C Compiler)
- **Standard**: C11
- **Flags**: `-Wall -Wextra -pedantic`

## Build Instructions

From the project directory, run:

```bash
gcc -std=c11 -Wall -Wextra -pedantic number_guess.c -o number_guess
```

## Run

```bash
./number_guess
```

## How to Play

1. The program generates a random number between 1 and 100.
2. Enter your guess when prompted.
3. After each guess, you'll be told if it was too high or too low.
4. Keep guessing until you find the correct number.
5. The program will display your total number of attempts at the end.

## Clean up

```bash
rm number_guess
```
