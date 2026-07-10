# CSV Reader — Build Instructions

## Prerequisites
- GCC compiler with C11 support
- Standard C library

## Compile
```bash
gcc -std=c11 -Wall -Wextra -pedantic csv_reader.c -o csv_reader
```

## Run
```bash
./csv_reader
```

The program expects `students.csv` to be in the **same directory** as the
executable.

## Custom CSV format
The CSV must have three fields per line, comma-separated:

    name,id,grade

Example:

    Alice,101,85
    Bob,102,92
    Charlie,103,78

## Error handling
- If `students.csv` is missing, `perror` prints a descriptive message.
- Malformed or empty lines are reported to stderr and skipped.
- Records beyond the first 128 are silently truncated (a warning is printed).
