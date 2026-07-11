# CSV Reader — BUILD.md

## Overview

Reads a CSV file (`students.csv`) with three fields per line (name, id, grade),
parses it line by line, and prints the records. Demonstrates file I/O, line-
delimited parsing, and error handling for missing files and malformed data.

## Requirements

- GCC (GNU C Compiler) with C11 support
- Standard C library

## Build

```bash
gcc -std=c11 -Wall -Wextra -pedantic csv_reader.c -o csv_reader
```

## Usage

```bash
./csv_reader
```

The program expects `students.csv` to be in the **same directory** as the
executable.

### CSV format

Three comma-separated fields per line:

```text
name,id,grade
```

Example:

```text
Alice,101,85
Bob,102,92
Charlie,103,78
```

### Sample output

```text
Reading students.csv...
Record 1: Alice (ID: 101) — Grade: 85
Record 2: Bob (ID: 102) — Grade: 92
Record 3: Charlie (ID: 103) — Grade: 78
3 records loaded.
```

## Error handling

- If `students.csv` is missing, `perror` prints a descriptive message.
- Malformed or empty lines are reported to stderr and skipped.
- Records beyond the first 128 are silently truncated (a warning is printed).

## Concepts Used

- `fopen` / `fclose` with NULL check and `perror`
- `fgets` for line-by-line file reading
- String splitting (`strtok_r` or manual delimiter scanning)
- `strtol` for safe numeric field parsing
- Basic CSV parsing without external libraries
