# BUILD.md — Student Database

## Compile

```sh
gcc -std=c11 -Wall -Wextra -pedantic student_db.c -o student_db
```

## Run

```sh
./student_db
```

## Usage

| Key | Action              |
|-----|---------------------|
| a   | Add a student       |
| l   | List all students   |
| s   | Search by student ID|
| q   | Quit                |

## Requirements

- C11 compiler (gcc, clang)
- No external libraries beyond the C standard library
