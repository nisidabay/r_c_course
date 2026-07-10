# References — Modern C (C11)

## Core References

| Resource | Why |
|----------|-----|
| *Effective C* (Seacord, 2nd ed, 2024) | The core C reference for this course. Covers safe C programming, undefined behavior, and modern C11/C17 practices. Every concept file in this course is designed to be understood alongside the corresponding chapter in Seacord. |
| GCC manual (`man gcc`) | Understanding compiler flags (`-std=c11`, `-Wall`, `-Wextra`, `-pedantic`, `-fsanitize=address`) and platform-specific behaviour. |

## Essential Tools

| Resource | Why |
|----------|-----|
| valgrind (`man valgrind`) | Memory leak detection and heap profiling. Used in `07_dynamic_mem` to verify `malloc`/`free` discipline. Run with: `valgrind --leak-check=full ./program` |
| AddressSanitizer (`-fsanitize=address`) | Runtime bounds checking and use-after-free detection. Compile with `-fsanitize=address -g` to catch buffer overflows, stack overflows, and heap corruption that valgrind might miss. |

## Inspiration

| Resource | Why |
|----------|-----|
| [Tony Banters - "Strings Aren't Real"](https://www.youtube.com/watch?v=fUVvfDkDb-Y) | The talk that inspired Group 04's `String_Slice` approach. Argues that null-terminated C strings are not real data types and demonstrates the `char*` + `size_t` pattern. |
| [string.c by tonybanters](https://github.com/tonybanters/string.c) | Source code for the fstab parser project in Group 04. A practical demonstration of zero-copy string processing with `String_Slice`. |

## What's NOT Here

- **K&R (*The C Programming Language*)** — Not included. The code style in K&R predates C99 and C11, uses banned functions (`strcpy`, `sprintf`, `scanf`), and teaches patterns that the Safe C Standard explicitly prohibits.
- **cppreference.com** — Not included as a primary reference. Online references change without versioning and mix standards. *Effective C* is the stable, curated source.
- **GDB** — Not included. This course focuses on static correctness (compiler warnings, Safe C Standard) and dynamic analysis (valgrind, AddressSanitizer). Debugging is out of scope.
