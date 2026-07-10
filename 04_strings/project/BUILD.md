# BUILD.md — fstab_parser

## Overview

A zero-copy `/etc/fstab` parser using `String_Slice` views, inspired by
Tony Banters' "Strings Aren't Real" video.

Every field is extracted as a `String_Slice` (pointer + length) — no
memory allocation, no copies, no `strtok` or `strcpy`.

## Prerequisites

- GCC 4.6+ (anything that supports C11)
- A Unix-like system with `/etc/fstab`

## Build

    gcc -std=c11 -Wall -Wextra -pedantic fstab_parser.c -o fstab_parser

## Run

    ./fstab_parser

### Example output

    ---
    device : UUID=54152408-d100-4435-af5f-ff6b8435df26
    mount  : /
    type   : ext4
    options: rw,relatime
    dump   : 0
    pass   : 1
    ---
    device : UUID=AF7A-D1C2
    mount  : /boot
    type   : vfat
    options: rw,relatime,fmask=0022,dmask=0022,codepage=437,iocharset=ascii,shortname=mixed,utf8,errors=remount-ro
    dump   : 0
    pass   : 2

## Data structures

### String_Slice

```c
typedef struct {
    char  *data;   /* pointer into the original buffer (no copy) */
    size_t len;    /* number of valid characters */
} String_Slice;
```

### Functions

| Function              | Purpose                                      |
|-----------------------|----------------------------------------------|
| `slice_from_cstring`  | Create a slice from a `'\0'`-terminated string |
| `slice_trim`          | Remove leading/trailing whitespace            |
| `slice_split`         | Split on a delimiter (mutates the argument)   |
| `slice_starts_with`   | Check if slice begins with a given prefix     |
| `slice_take`          | Keep first *n* characters                     |
| `slice_drop`          | Remove first *n* characters                   |
| `print_slice`         | Write a slice to stdout character by character |

## Constraints

- Input lines must be ≤ 511 characters (512-byte buffer).
- Tab characters are treated as whitespace by `slice_trim` (isspace)
  but are **not** split by `slice_split` (which uses ' '). If your
  `/etc/fstab` uses tabs between fields, the parser will coalesce
  them into a single field. *(The task spec says space delimiter.)*
