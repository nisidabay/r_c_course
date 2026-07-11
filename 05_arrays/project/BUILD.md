# Grade Statistics Tool — BUILD.md

## Overview

Reads up to 20 student scores (0–100) from stdin, computes min/max/average
and passing count (≥60), sorts the scores using selection sort, and displays
the results. The first C project that works with a **collection** of data
rather than individual values.

## Requirements

- GCC with C11 support (tested with gcc 14+)
- Standard C library

## Build

```bash
gcc -std=c11 -Wall -Wextra -pedantic grade_stats.c -o grade_stats
```

## Usage

```bash
./grade_stats
```

Enter one score per line (0–100). Press **Ctrl-D** (EOF on Linux/macOS)
or **Ctrl-Z then Enter** (on Windows) to signal end-of-input.

```text
Enter scores (one per line). Press Ctrl-D when done.
85
92
57
73
44
68
^D
Scores entered: 6
Sorted scores: 44 57 68 73 85 92
Min: 44, Max: 92, Average: 69.83
Passing (>=60): 4 / 6
```

## Concepts Used

- `fgets` + `strtol` for safe numeric input
- `sizeof` trick for array capacity
- Selection sort (in-place)
- `size_t` from `<stddef.h>`
- Functions with arrays passed by pointer
- EOF-sentinel loop pattern
