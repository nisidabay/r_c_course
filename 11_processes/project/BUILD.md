# Journal App — BUILD.md

## Overview

A personal journal that integrates with your system editor. Uses all concepts from groups 01–11.

## Requirements

- GCC (C11)
- SQLite3 development libraries (`libsqlite3-dev` on Debian, `sqlite3` on Arch)
- A terminal text editor (vi, nvim, emacs, etc.)

## Build

```bash
gcc -std=c11 -Wall -Wextra -pedantic journal.c -o journal -lsqlite3
```

## Usage

```bash
# Create a new entry (opens $EDITOR)
./journal new

# List recent entries
./journal list

# Edit an existing entry
./journal edit 1

# Use a custom database
./journal --db ~/myjournal.db new

# Get help
./journal --help
```

## How It Works

| Concept | What it does |
|---------|-------------|
| `fork`+`exec`+`waitpid` (01) | Launches the editor and waits for it |
| `execlp`/`execvp` (02) | Finds the editor via PATH search |
| `getenv` (06) | Reads `$EDITOR`, `$HOME` |
| `getopt_long` (08) | Parses `--db` and `--help` flags |
| `mkdir` (08) | Creates `~/.journal/` on first run |
| `snprintf` (04) | Builds file paths and SQL queries |
| `sqlite3` (07) | Persistent entry storage |
| `perror` (09) | Error reporting on failures |

## Concepts Exercised

| Group | Concept |
|-------|---------|
| 01 | `printf`, `fgets`, `strcspn` |
| 03 | Functions, `EXIT_SUCCESS`/`EXIT_FAILURE` |
| 04 | `snprintf`, strings |
| 06 | Pointers, `NULL` checks |
| 07 | `malloc`, `free` |
| 08 | Structs (`struct option`) |
| 09 | Files (`fopen`, `fclose`, `fread`, `fseek`) |
| 11 (Processes) | All concepts 01–08 |
