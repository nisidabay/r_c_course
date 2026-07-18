# Number Guessing Game — BUILD.md

## Overview

A classic number guessing game: the program picks a random number between 1
and 100, and you guess until you find it. Each guess gets a "too high" or
"too low" hint. Demonstrates loops (`do-while`), conditionals, random number
generation, and the `fgets` + `consume_remaining` guard pattern inside a
game loop.

## Requirements

- GCC (GNU C Compiler) with C11 support
- Standard C library

## Build

```bash
gcc -std=c11 -Wall -Wextra -pedantic number_guess.c -o number_guess
```

## Usage

```bash
./number_guess
```

The program generates a random number between 1 and 100. Enter your guess
when prompted. After each guess, you'll be told if it was too high or too
low. Keep guessing until you find the correct number.

```text
I'm thinking of a number between 1 and 100.
Enter your guess: 50
Too high!
Enter your guess: 25
Too low!
Enter your guess: 37
Too high!
Enter your guess: 31
Too low!
Enter your guess: 34
Correct! You got it in 5 attempts.
```

## Concepts Used

- `do-while` loop for the game loop
- `if-else` chain for hint logic
- `rand()` / `srand()` + `time()` for random number generation
- `fgets` + `strtol` for safe numeric input
- `consume_remaining` guard inside an iterative loop
- Single `fgets` per iteration with truncation detection
