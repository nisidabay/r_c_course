# Group 01: Hello, World!

> How do I write, compile, and run a C program?

## Concepts (5)

| File | One Question |
|------|-------------|
| `01_hello_world.c` | How do I write a minimal C program? |
| `02_data_types.c` | What are C's basic types and how big are they? |
| `03_arithmetic.c` | How do I do math in C? |
| `04_comments_format.c` | How do I document code that the compiler ignores? |
| `05_simple_input.c` | How do I read text from the user and parse a number? |

## Exercises (6)

Write your code in the stub files below, then check against the solutions:

| # | Stub (edit this) | Solution (reference) | Description |
|---|-----------------|---------------------|-------------|
| 1 | `ex_01_hello_world.c` | `ex_01_hello_world_solution.c` | Print "Hello, World!" |
| 2 | `ex_02_data_types.c` | `ex_02_data_types_solution.c` | Declare and print `int`, `double`, `char` |
| 3 | `ex_03_arithmetic.c` | `ex_03_arithmetic_solution.c` | Arithmetic on two ints |
| 4 | `ex_04_comments.c` | `ex_04_comments_solution.c` | Compute future age with comments |
| 5 | `ex_05_input.c` | `ex_05_input_solution.c` | Read name + number, print greeting |
| 6 | `ex_06_challenge.c` | `ex_06_challenge_solution.c` | Age in years and months from birth year |

Verify your work by running all solutions:

```bash
bash 01_hello/exercises/verify-exercises.sh
```

## Project: MadLibs

A fill-in-the-blank word game — `project/madlibs.c`. Reads five user inputs and
weaves them into a story. See [`project/BUILD.md`](project/BUILD.md).

## Build

```bash
# Any concept
gcc -std=c11 -Wall -Wextra -pedantic concept/01_hello_world.c -o /tmp/demo && /tmp/demo

# All exercises
bash exercises/verify-exercises.sh

# The project
cd project && gcc -std=c11 -Wall -Wextra -pedantic madlibs.c -o madlibs && ./madlibs
```
