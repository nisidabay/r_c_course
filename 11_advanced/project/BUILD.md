# Generic Sorting Framework — BUILD.md

## Overview

A C program demonstrating a generic sorting framework using `qsort` with
runtime-selectable comparators via function pointers. Sorts an array of
product structs by name (alphabetical), price (ascending), or quantity
(descending). This is the capstone project pulling together concepts from
all 10 groups.

## Requirements

- GCC (or any C11-compatible compiler)
- GNU/Linux, macOS, or WSL

## Build

```bash
gcc -std=c11 -Wall -Wextra -pedantic generic_sorter.c -o generic_sorter
```

## Usage

```bash
./generic_sorter
```

The program loops, reading a single character from stdin:

| Key | Action                            |
|-----|-----------------------------------|
| `n` | Sort by **name** (alphabetical)    |
| `p` | Sort by **price** (ascending)      |
| `q` | Sort by **quantity** (descending)  |
| `x` | Exit the program                   |

```text
Current products:
  Apple       — $1.50  (qty: 100)
  Banana      — $0.75  (qty: 150)
  Cherry      — $3.00  (qty: 50)
  Date        — $2.50  (qty: 75)

[n]ame, [p]rice, [q]uantity, e[x]it: p
  Banana      — $0.75  (qty: 150)
  Apple       — $1.50  (qty: 100)
  Date        — $2.50  (qty: 75)
  Cherry      — $3.00  (qty: 50)

[n]ame, [p]rice, [q]uantity, e[x]it: x
```

## Concepts Exercised (groups 01–10)

| Group | Concept                           |
|-------|-----------------------------------|
| 01    | Basic I/O (`printf`)              |
| 02    | Types, variables, `do-while` loop |
| 03    | Functions, prototypes             |
| 04    | Strings, `snprintf`, `strcmp`     |
| 05    | Arrays, `sizeof` trick            |
| 06    | Pointers, function pointers       |
| 07    | Dynamic memory (`malloc`/`free`)  |
| 08    | `struct` definition and usage     |
| 09    | File I/O (`fprintf` to stderr)    |
| 10    | `qsort`, `_Generic` (optional)    |
