# BUILD.md

## Requirements

- GCC (GNU C Compiler) with C11 support

## Compilation

```bash
gcc -std=c11 -Wall -Wextra -pedantic array_reverse.c -o array_reverse
```

## Usage

```bash
./array_reverse
```

Enter 10 integers (one per line). The program will display the original
order followed by the reversed order.

## Concepts Used

- `fgets()` / `sscanf()` for robust input parsing
- Pointer parameters (`int *arr, size_t len`)
- Pointer arithmetic (`*(arr + i)`)
- Two-pointer swap technique (`start` and `end` walking toward each other)
- In-place reversal via pointer dereference (`*start`, `*end`)
- Only concepts from groups 01–06 (no VLAs, no malloc, no struct, etc.)
