# Practical C (Modern C11)

> Code first. Theory on demand.

```bash
gcc -std=c11 -Wall -Wextra -pedantic 01_hello/concept/01_hello_world.c -o /tmp/demo && /tmp/demo
```

---

## Philosophy

This course follows the **"Code first. Theory on demand."** approach. 
Each concept is a compilable `.c` file that runs immediately. Explanations live
inside the file as comments under `// Thinking in C:` — you read them *after*
the code compiles and executes. Learn C the way you'll use it: to write CLI
tools for Linux.

**One question per file.** Every concept file answers exactly one question.
`01_array_declaration.c` answers "How do I declare and initialize an array?"
`03_string_slice.c` answers "How do I represent a string without copying?" This
keeps each exposure short, focused, and memorable.

**Tony Banters' "Strings Aren't Real" (Group 04).** Group 04 introduces
`String_Slice` — a `char*` + `size_t` struct that replaces the traditional
null-terminated C string model. The insight (from Tony Banters' talk) is that C
strings are not real data types: they're just pointers with a convention. By
bundling the length alongside the pointer, every string operation becomes O(1)
for length, bounds-safe, and zero-copy. The group's project (an fstab parser)
demonstrates the approach end-to-end.

**Safe C Standard.** This course enforces a strict safe subset of C11. Banned
functions include `strcpy`, `strcat`, `sprintf`, `scanf`, `atoi`, and `atof`.
All input uses `fgets` + `sscanf`. All string building uses `snprintf`. All
number parsing uses `strtol`/`strtod`. Every `malloc`/`calloc`/`realloc` call
is followed by a NULL check with `perror`. See the [Safe C Standard](#safe-c-standard) section for the full table.

**Cross-reference.** This course is organized into groups, each with: concept
files (`.c`), exercises (`.c` with solutions), a project (with `BUILD.md`), and
a `verify-exercises.sh` script.
The top-level `verify.sh` compiles every file and runs every verification
script in the whole course.

---

## The Path (10 groups)

| # | Group | One Question | Project |
|---|-------|-------------|---------|
| 01 | `01_hello/` | How do I write, compile, and run a C program? | madlibs |
| 02 | `02_control/` | How do I make decisions and repeat work in C? | number_guess |
| 03 | `03_functions/` | How do I define, call, and organize reusable code? | calculator |
| 04 | `04_strings/` | How do I handle text safely without copying? | fstab_parser |
| 05 | `05_arrays/` | How do I store and process collections of data? | grade_stats |
| 06 | `06_pointers_101/` | What is a pointer and how do I use one? | array_reverse |
| 07 | `07_dynamic_mem/` | How do I allocate memory at runtime? | dynamic_list |
| 08 | `08_structs/` | How do I group related data into a custom type? | student_db |
| 09 | `09_files/` | How do I read and write files? | csv_reader |
| 10 | `10_advanced/` | How do I use enums, function pointers, and `_Generic`? | generic_sorter |

Each group has 4–7 concept files, 6–7 exercises (with solutions), a project with `BUILD.md`, and a `verify-exercises.sh` script.

---

## Quick Start

Each group is self-contained. Start at group 01:

```bash
# Run the first concept
gcc -std=c11 -Wall -Wextra -pedantic 01_hello/concept/01_hello_world.c -o /tmp/demo && /tmp/demo

# Work through a concept, edit, recompile
gcc -std=c11 -Wall -Wextra -pedantic 01_hello/concept/02_data_types.c -o /tmp/demo && /tmp/demo
```

**Exercises.** Each group has exercises with matching solution files. To verify your work:

```bash
# Run the group's verification script (compiles and tests all solutions)
bash 01_hello/exercises/verify-exercises.sh

# Or compile an exercise and its solution side by side
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

The following functions are **banned** in this course. Every occurrence has been replaced with a safe alternative.

| Banned | Safe Replacement | Why |
|--------|-----------------|-----|
| `strcpy` | `snprintf(dst, sizeof dst, "%s", src)` or `memcpy` with explicit bounds | No bounds checking; buffer overflow |
| `strcat` | `snprintf(dst + offset, remaining, "%s", src)` | No bounds checking; buffer overflow |
| `sprintf` | `snprintf(buf, sizeof buf, fmt, ...)` | No bounds checking; buffer overflow |
| `scanf` | `fgets(buf, sizeof buf, stdin)` + `sscanf(buf, ...)` | No bounds checking on input; undefined behavior on overflow |
| `atoi` | `strtol(str, &endptr, 10)` | No error detection; undefined on overflow |
| `atof` | `strtod(str, &endptr)` | No error detection; undefined on overflow |
| `gets` | `fgets(buf, sizeof buf, stdin)` | Buffer overflow (removed from C11 standard) |

**Memory allocation rule.** Every `malloc`, `calloc`, or `realloc` call must be followed by a NULL check:

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

## Input Safety Best Practices

### The problem: `fgets` may not read a full line

C11, §7.21.7.2:

> *"The fgets function reads **at most one less than the number of characters specified by n** from the stream... No additional characters are read after a new-line character (which is retained) or after end-of-file."*

`fgets(buf, 32, stdin)` reads **at most 31 characters**. If the user types 50, the remaining 19 characters (plus `\n`) stay in `stdin`. The **next** `fgets` will read them, not the user's intended input.

The same applies to `getchar()`: it reads exactly **one** byte. The `\n` from Enter stays behind.

### How to detect and fix it

After every `fgets` call, check whether the buffer contains the newline that signals a complete line was read:

```c
#include <stdio.h>
#include <string.h>

/*
 * consume_remaining — discard characters from stdin until \n or EOF.
 * Needed only when fgets truncates (buffer too small for the input line)
 * or after getchar().
 *
 * Calling this unconditionally is safe but unnecessary — fgets already
 * consumes the \n when the input fits. Only call it when truncation is
 * detected.
 */
static void consume_remaining(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main(void)
{
    char buf[16];  /* intentionally small for demonstration */

    printf("Enter a long string: ");
    if (fgets(buf, sizeof buf, stdin) == NULL)
        return 1;

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
        /* Truncation detected — consume the rest of the line */
        consume_remaining();
    }

    printf("First 15 chars: %s\n", buf);

    return 0;
}
```

### When it's needed vs. not

| Scenario | Cleanup needed? | Reason |
|----------|----------------|--------|
| `fgets()` with no truncation (buffer large enough for typical input) | ❌ No | `fgets` consumed everything including `\n`. The check `buf[len-1] != '\n'` returns false. |
| `fgets()` with truncation (buffer too small for the line typed) | ✅ Yes | Characters beyond `size-1` remain in stdin. The next read will pick up garbage. |
| `getchar()` for menu selection | ✅ Yes | `getchar()` reads exactly one byte; `\n` stays in stdin. |
| `fflush(stdin)` | ❌ Never | **Undefined behavior.** C11, §7.21.5.2: `fflush` on an input stream is UB. The standard explicitly says so. |

### The guard pattern

The canonical way to call `consume_remaining` only when needed:

```c
char buf[32];
if (fgets(buf, sizeof buf, stdin) == NULL)
    return 1;

size_t len = strlen(buf);
if (len > 0 && buf[len - 1] != '\n') {
    consume_remaining();  /* input was truncated — clear the residue */
}
```

After `getchar()`, call it unconditionally — the `\n` is always there:

```c
int choice = getchar();
consume_remaining();  /* getchar always leaves \n behind */
```

### What NOT to do

| Anti-pattern | Why it's wrong |
|-------------|----------------|
| `fflush(stdin)` | Undefined behavior per C11 §7.21.5.2. Works on some implementations, crashes on others, and the standard guarantees nothing. |
| `while(getchar() != '\n');` without `EOF` check | Infinite loop if stdin closes (pipe or redirected input). Always check for `EOF`. |
| Consuming unconditionally after every `fgets` | Wastes cycles and can discard valid input when the line fit perfectly. Use the `buf[len-1] != '\n'` guard. |

### Reference

- ISO/IEC 9899:2011 (C11), §7.21.5.2 — `fflush` behavior on input streams
- ISO/IEC 9899:2011 (C11), §7.21.7.2 — `fgets` semantics
- K.3.5.4.1 (Annex K) — recommended practice for `fgets` and newline detection

### Where you'll see it in this course

The `consume_remaining` helper (or an inline equivalent) appears in every file that reads interactive input:

| File | Why it's there |
|------|---------------|
| `01_hello/concept/05_simple_input.c` | Two sequential `fgets` calls; the second would read garbage if the first truncated. |
| `01_hello/exercises/ex_05_input_solution.c` | Same pattern — name buffer, then number buffer. |
| `01_hello/exercises/ex_06_challenge_solution.c` | Two small `char[12]` buffers for year input. |
| `01_hello/project/madlibs.c` | Five sequential `fgets` calls — one truncated input would poison every subsequent prompt. |
| `02_control/project/number_guess.c` | Single `fgets` in a loop — truncation poisons the next iteration. |
| `03_functions/project/calculator.c` | Three sequential `fgets` calls per iteration (number, operator, number). |
| `08_structs/exercises/ex_07_challenge_solution.c` | Four `fgets` calls per student record. |
| `08_structs/project/student_db.c` | `getchar()` for menu selection — the `\n` is always there. |

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

---

## License

This course is provided for educational purposes. See individual file headers
for attribution.
