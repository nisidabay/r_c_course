# Permission CLI — BUILD.md

## Overview

A CLI tool that reads permission names ("read", "write", "execute") and builds
the corresponding Unix-style permission mask using bitwise OR. Demonstrates
all concepts from Group 02: binary representation, bitwise operators, masks,
and the real-world application of permission flags.

## Requirements

- GCC (GNU C Compiler) with C11 support
- Standard C library

## Build

```bash
gcc -std=c11 -Wall -Wextra -pedantic permission_cli.c -o permission_cli
```

## Usage

```bash
./permission_cli
```

Enter permission names separated by spaces:

```text
=== Permission Mask Builder ===
Enter permission names (read, write, execute) separated by
spaces, or 'q' to quit.

permissions: read write
  Binary : 0000 0110
  Octal  : 06
  Decimal: 6
  Symbolic: rw-

permissions: read write execute
  Binary : 0000 0111
  Octal  : 07
  Decimal: 7
  Symbolic: rwx

permissions: read execute
  Binary : 0000 0101
  Octal  : 05
  Decimal: 5
  Symbolic: r-x

permissions: q
Goodbye!
```

## Concepts Used

- Binary representation and bit inspection
- Bitwise OR (`|`) to combine flags
- Bitwise AND (`&`) to test flags (in `print_symbolic`)
- Shift-free design — masks defined as integer constants
- `strtok` for simple tokenisation
- Permission masks as a real-world bitwise pattern
