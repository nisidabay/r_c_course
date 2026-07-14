# Array Reversal — BUILD.md

## Overview

Reads 10 integers from stdin, displays them in original order, then reverses
the array **in place** using a two-pointer technique. No second array, no
malloc — pure pointer arithmetic. This is the first project where students
use pointers directly as iteration and mutation tools.

## Requirements

- GCC (GNU C Compiler) with C11 support
- Standard C library

## Build

```bash
gcc -std=c11 -Wall -Wextra -pedantic array_reverse.c -o array_reverse
```

## Usage

```bash
./array_reverse
```

```text
Enter 10 integers (one per line):
1
2
3
4
5
6
7
8
9
10

Original: 1 2 3 4 5 6 7 8 9 10
Reversed: 10 9 8 7 6 5 4 3 2 1
```

## Concepts Used

- `fgets` + `strtol` for safe numeric input
- Pointer parameters (`int *arr, size_t len`)
- Pointer arithmetic (`*(arr + i)`)
- Two-pointer swap technique (`start` and `end` walking toward each other)
- In-place reversal via pointer dereference (`*start`, `*end`)
- Only concepts from groups 01–06 (no VLAs, no malloc, no struct)
