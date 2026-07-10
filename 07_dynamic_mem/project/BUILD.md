# BUILD.md — Dynamic Contact List

## Overview
A simple C program that manages a dynamic array of contacts (name + phone)
using `malloc`/`realloc`/`free` with full NULL-checking.

## Compilation

```sh
gcc -std=c11 -Wall -Wextra -pedantic dynamic_list.c -o dynamic_list
```

## Usage

Run the program:

```sh
./dynamic_list
```

Enter contacts in the format `name,phone`:
```
>> Alice,555-1234
>> Bob,555-5678
```

Commands:
- `p` — print all contacts
- `q` — quit

## Requirements met

| Requirement        | Status |
|--------------------|--------|
| struct Contact     | ✅     |
| struct ContactList | ✅     |
| contactlist_create | ✅     |
| contactlist_add    | ✅ realloc with temp ptr, NULL-checked |
| contactlist_print  | ✅ snprintf for display |
| contactlist_free   | ✅ frees all memory |
| fgets+sscanf       | ✅     |
| snprintf           | ✅     |
| NULL-checked malloc/realloc | ✅ |
| realloc temp pointer       | ✅ |
| Concepts 01-07 only       | ✅ |
| C11 + Wall + Wextra + pedantic | ✅ |
