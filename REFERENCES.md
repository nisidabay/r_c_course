# References — Modern C (C11)

> Where this course comes from.

---

## Foundations

These are the works that shaped the design and safety standards of this course.
We don't expect you to read them — but if you ever wonder *"why does this
course do X instead of Y?"*, the answer lives here.

---

### *Effective C* (Seacord, 2nd ed, 2024)

The language-lawyer backbone. Seacord codifies safe C11/C17 practices,
undefined behavior classification, and the rationale behind banning the
functions this course bans. Every concept file in this course maps to a
Seacord chapter — not because the course is "based on the book", but because
Seacord is *the* authoritative modern C reference that says *what* to do and,
more importantly, *why*.

### GNU/Linux

This course is built on and for GNU/Linux. The compiler is `gcc`, the
toolchain is POSIX, the process model (fork, exec, pipe) is Unix. Every
command in every BUILD.md works on a stock Arch/Debian/Fedora system. The
course doesn't teach Linux — it teaches C *through* Linux, because that's
where C and the OS meet.

### The C Standards Committee (ISO/IEC 9899)

The C11 standard (and its C17 correction) defines what the language is. When
this course says "this is undefined behavior per C11 §7.21.5.2", it's not
being pedantic — it's citing the contract between the programmer and the
compiler. Understanding that contract is the whole point.

---

## Inspiration

### "Strings Aren't Real" — Tony Banters

[Talk](https://www.youtube.com/watch?v=fUVvfDkDb-Y) |
[Source code](https://github.com/tonybanters/string.c)

The idea that C strings are not a real data type — just a pointer with a
convention — came from this talk. Group 04's `String_Slice` (a `char*` +
`size_t` struct) is a direct application of Tony's approach. Every string
operation becomes O(1) for length, bounds-safe, and zero-copy. The group's
project (an fstab parser) demonstrates it end-to-end.

### The Linux Kernel

The kernel is the largest and most battle-tested C codebase in existence.
This course looks to it not for code style (kernel style is too specialized
for a teaching course) but for *attitude*: safety through discipline,
simplicity over cleverness, and the conviction that the programmer — not
the language — is responsible for correctness.

---

## What's Not Here

- **K&R (*The C Programming Language*)** — A classic, but pre-dates C99 and
  C11. It uses `strcpy`, `sprintf`, and `gets` without warning. Teaching its
  patterns would contradict this course's Safe C Standard.
- **cppreference.com** — Changes without versioning. *Effective C* is the
  stable, curated source.
- **GDB** — This course focuses on static correctness (compiler warnings,
  Safe C Standard) and dynamic analysis (valgrind, AddressSanitizer).
  Interactive debugging is a separate skill, out of scope here.
