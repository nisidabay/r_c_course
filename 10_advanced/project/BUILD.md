# Generic Sorting Framework — BUILD.md

## Overview

A C program demonstrating a generic sorting framework using `qsort` with
runtime-selectable comparators via function pointers. Covers concepts from
groups 01 through 10.

## Requirements

- GCC (or any C11-compatible compiler)
- GNU/Linux, macOS, or WSL

## Build

```sh
gcc -std=c11 -Wall -Wextra -pedantic generic_sorter.c -o generic_sorter
```

## Run

```sh
./generic_sorter
```

## Usage

The program loops, reading a single character from stdin:

| Key | Action                        |
|-----|-------------------------------|
| `n` | Sort by **name** (alphabetical) |
| `p` | Sort by **price** (ascending)   |
| `q` | Sort by **quantity** (descending) |
| `x` | Exit the program               |

## Concepts exercised (groups 01–10)

| Group | Concept                     |
|-------|-----------------------------|
| 01    | Basic I/O (`printf`)        |
| 02    | Types, variables, `struct`  |
| 03    | Strings, `snprintf`, `strcmp` |
| 04    | Loops (`for`, `do-while`)   |
| 05    | Functions, prototypes       |
| 06    | Arrays, pointers, function pointers |
| 07    | Dynamic memory (`malloc`/`free`) |
| 08    | File I/O (`fprintf`, `scanf`) |
| 09    | Preprocessor, `_Generic`    |
| 10    | Sorting (`qsort`)           |
