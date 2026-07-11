# Student Database — BUILD.md

## Overview

An interactive menu-driven program that manages a fixed-size student database
with add, list, and search-by-ID operations. Each student record stores a
name, ID number, and grade. This is the first project using multiple structs
and a menu loop driven by `getchar()`.

## Requirements

- GCC (GNU C Compiler) with C11 support
- Standard C library

## Build

```bash
gcc -std=c11 -Wall -Wextra -pedantic student_db.c -o student_db
```

## Usage

```bash
./student_db
```

| Key | Action              |
|-----|---------------------|
| a   | Add a student       |
| l   | List all students   |
| s   | Search by student ID|
| q   | Quit                |

```text
Database initialized (max 100 students).

[a]dd, [l]ist, [s]earch, [q]uit: a
Name: Alice
ID: 101
Grade: 85

[a]dd, [l]ist, [s]earch, [q]uit: a
Name: Bob
ID: 102
Grade: 92

[a]dd, [l]ist, [s]earch, [q]uit: l
1: Alice (ID: 101) — Grade: 85
2: Bob (ID: 102) — Grade: 92

[a]dd, [l]ist, [s]earch, [q]uit: s
Enter ID: 101
Found: Alice (ID: 101) — Grade: 85

[a]dd, [l]ist, [s]earch, [q]uit: q
```

## Concepts Used

- `struct` definition with multiple member types (`char[]`, `int`, `float`)
- Array of structs for the database
- Menu loop with `getchar()` + `consume_remaining` guard
- `fgets` + `strtol` for safe numeric input
- Linear search by student ID
- Four `fgets` calls per add operation with truncation protection
