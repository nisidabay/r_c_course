# Grade Statistics Tool — BUILD.md

## Overview

Reads up to 20 student scores (0–100) from stdin, computes min/max/average
and passing count (>=60), sorts the scores using selection sort, and displays
the results.

## Requirements

- GCC with C11 support (tested with gcc 14+)
- Make (optional – you can compile manually)

## Compilation

```sh
gcc -std=c11 -Wall -Wextra -pedantic grade_stats.c -o grade_stats
```

## Usage

```sh
./grade_stats
```

Enter one score per line (0–100). Press **Ctrl-D** (EOF on Linux/macOS)
or **Ctrl-Z then Enter** (on Windows) to signal end-of-input.

### Sample input

```
85
92
57
73
44
68
```

### Sample output

```
  Sorted scores and statistics ...
```

## Concepts used

- `fgets` + `sscanf` for safe input
- `sizeof` trick for array capacity
- Selection sort (in-place)
- `size_t` from `<stddef.h>`
- Functions with arrays passed by pointer
- C11 standard mode with pedantic flags
