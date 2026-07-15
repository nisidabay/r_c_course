# Course Documentation

> Everything you need to use this course effectively.

---

## Quick Start

Each group is self-contained. Start at group 01:

```bash
# Run the first concept
gcc -std=c11 -Wall -Wextra -pedantic 01_hello/concept/01_hello_world.c -o /tmp/demo && /tmp/demo

# Work through a concept, edit, recompile
gcc -std=c11 -Wall -Wextra -pedantic 01_hello/concept/02_data_types.c -o /tmp/demo && /tmp/demo
```

**Exercise solutions.** Each group has solution files that demonstrate the
canonical implementation. Run them to see the expected output:

```bash
# Run the group's verification script (compiles and tests all solutions)
bash 01_hello/exercises/verify-exercises.sh

# Or compile and run a specific solution directly
gcc -std=c11 -Wall -Wextra -pedantic 01_hello/exercises/ex_01_hello_world_solution.c -o /tmp/demo && /tmp/demo
```

**Projects.** Every project has a `BUILD.md` with compile and run instructions:

```bash
# Build the group 01 project
cd 01_hello/project
# Read BUILD.md for instructions
gcc -std=c11 -Wall -Wextra -pedantic madlibs.c -o madlibs && ./madlibs
```

**Full verification.** From the course root, run the top-level `verify.sh` to
compile every concept, every solution, every project, run all verification
scripts, and check for forward references:

```bash
bash verify.sh
```

---

## Feature Flags

All code in this course is compiled with:

```bash
-std=c11 -Wall -Wextra -pedantic
```

| Flag | Purpose |
|------|---------|
| `-std=c11` | Use the C11 standard (anonymous structs, `_Generic`, designated initializers). |
| `-Wall` | Enable most common warnings (misspelled format specifiers, unused variables). |
| `-Wextra` | Enable additional warnings (signed/unsigned comparison, implicit fallthrough). |
| `-pedantic` | Reject non-standard extensions; enforce strict ISO C compliance. |

**POSIX extensions.** Some concept files use POSIX functions (`strdup`, `strtok_r`). These files include:

```c
#define _POSIX_C_SOURCE 200809L
```

This define is placed at the top of the file (before any `#include`) and is
documented in the file's comments. You do not need to pass it on the command
line — it's handled per-file where needed.

**No extra flags for C11 features.** C11 features like `_Generic` selections,
anonymous structs/unions, and designated initializers are part of the standard
and require no special flags beyond `-std=c11`.

---

## Safe C Standard

The following functions are **banned** in this course. Every occurrence has
been replaced with a safe alternative.

| Banned | Safe Replacement | Why |
|--------|-----------------|-----|
| `strcpy` | `snprintf(dst, sizeof dst, "%s", src)` or `memcpy` with explicit bounds | No bounds checking; buffer overflow |
| `strcat` | `snprintf(dst + offset, remaining, "%s", src)` | No bounds checking; buffer overflow |
| `sprintf` | `snprintf(buf, sizeof buf, fmt, ...)` | No bounds checking; buffer overflow |
| `scanf` | `fgets(buf, sizeof buf, stdin)` + `sscanf(buf, ...)` for strings; `strtol(buf, &endptr, 10)` for numbers | No bounds checking on input; undefined behavior on overflow |
| `atoi` | `strtol(str, &endptr, 10)` | No error detection; undefined on overflow |
| `atof` | `strtod(str, &endptr)` | No error detection; undefined on overflow |
| `gets` | `fgets(buf, sizeof buf, stdin)` | Buffer overflow (removed from C11 standard) |

**Memory allocation rule.** Every `malloc`, `calloc`, or `realloc` call must be
followed by a NULL check:

```c
int *arr = malloc(n * sizeof(int));
if (arr == NULL) {
    perror("malloc");
    return 1;
}
```

Use `perror` (from `<stdio.h>`) to print the system error message. It's the
idiomatic C way to report what went wrong.

---

## Input Safety

### The one true input pattern

Every file in this course that reads a number from the user follows this exact pattern:

```c
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[64];
    int num;

    printf("Enter an integer: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    buf[strcspn(buf, "\n")] = '\0';   // strip trailing newline

    char *endptr;
    errno = 0;
    long val = strtol(buf, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    if (endptr == buf || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Out of int range\n");
        return EXIT_FAILURE;
    }
    num = (int)val;

    // ... use num ...

    return EXIT_SUCCESS;
}
```

This pattern is repeated identically in every file. There is exactly one way to read integer input in this course.

**For numeric input** — `fgets` + `strtol` with full `errno`/`endptr` validation (see pattern above).

**For non-numeric input** — `fgets` + `sscanf` is acceptable (reading names, splitting tokens, etc.).

**Why not `atoi` or `scanf`?** `atoi` has no error detection at all. `scanf` skips whitespace and can leave unread input in the buffer, causing subtle bugs. With `fgets` you control exactly what gets read.

**Why not `consume_remaining`?** With properly sized buffers (64-256 bytes), the entire input line almost always fits in a single `fgets` call. Using `strcspn(buf, "\n")` to strip the trailing newline is all that's needed — no `consume_remaining`, no `fflush(stdin)` (which is undefined behavior per C11 §7.21.5.2).

### File and memory patterns

**File opening** — every file follows this exact pattern:
```c
FILE *fp = fopen("filename", "r");
if (fp == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
}
```

**Memory allocation** — every allocation follows this exact pattern:
```c
int *arr = malloc(n * sizeof(*arr));
if (arr == NULL) {
    perror("malloc");
    return EXIT_FAILURE;
}
```

### What NOT to do for NUMERIC input

| Anti-pattern | Why it's wrong |
|-------------|----------------|
| `atoi` / `atof` | No error detection; undefined on overflow |
| `scanf("%d", ...)` directly (without fgets) | Skips whitespace, leaves unread input; no bounds checking |
| `fflush(stdin)` | Undefined behavior per C11 §7.21.5.2 |
| `consume_remaining` | Unnecessary with properly sized buffers; adds complexity |

**`sscanf` is fine for non-numeric input** (strings, formatted tokens, etc.).

---

## Fibonacci Study System

This course uses **Fibonacci-spaced repetition** to schedule reviews. The
rhythm is 1–2–3–5–8 days between successive reviews of the same unit, following
the Fibonacci sequence.

**How it works.**

A `learning_schedule.md` at the course root defines the full study plan. Each
row specifies a day, a session number, a unit (group name), and an activity.
The schedule interleaves new units with reviews of earlier ones so that every
unit is seen 5 times total (1 introduction + 4 reviews).

**`regenerate_crons.sh`.** Run this script from the course root to rebuild the
`.fibonacci/queue/` directory:

```bash
./regenerate_crons.sh
```

The script reads `learning_schedule.md`, parses the table, and creates one file
per session in `.fibonacci/queue/session_NNN.md`. Each file contains the unit
name, the activity description, and instructions to delete the file when done.

**Using the queue.**

```bash
# See what's next
ls .fibonacci/queue/ | head -1

# See how many sessions remain
ls .fibonacci/queue/ | wc -l

# When you finish a session, remove its file
rm .fibonacci/queue/session_001.md

# Review the full queue
ls .fibonacci/queue/
```

**The Fibonacci rhythm.** Sessions are spaced so that:
- **1st review**: 2 days after introduction
- **2nd review**: 3 days after 1st review
- **3rd review**: 5 days after 2nd review
- **4th review**: 8 days after 3rd review

This means each unit is revisited at progressively longer intervals, moving
knowledge from working memory into long-term retention.
