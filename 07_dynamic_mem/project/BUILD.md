# Dynamic Contact List — BUILD.md

## Overview

A simple C program that manages a dynamic array of contacts (name + phone)
using `malloc` / `realloc` / `free` with full NULL-checking. This is the
first project where memory is allocated at runtime — the contact list grows
as entries are added, with no arbitrary capacity limit.

## Requirements

- GCC (GNU C Compiler) with C11 support
- Standard C library
- Valgrind (optional, for memory leak verification)

## Build

```bash
gcc -std=c11 -Wall -Wextra -pedantic dynamic_list.c -o dynamic_list
```

## Usage

```bash
./dynamic_list
```

Enter contacts in the format `name,phone`:

```text
>> Alice,555-1234
>> Bob,555-5678
>> p
1: Alice — 555-1234
2: Bob — 555-5678
>> q
```

Commands:
- `name,phone` — add a contact
- `p` — print all contacts
- `q` — quit

## Concepts Used

- `struct Contact` and `struct ContactList` type definitions
- `contactlist_create` — initializes the dynamic array
- `contactlist_add` — `realloc` with temp pointer and NULL check
- `contactlist_print` — `snprintf` for formatted display
- `contactlist_free` — frees all memory
- `fgets` + `strtol` for safe input
- NULL-checked `malloc` / `realloc`
- `realloc` temp pointer pattern (never assign directly to the source)
- Concepts from groups 01–07 only
