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
the code compiles and executes.

**One question per file.** Every concept file answers exactly one question.
`01_array_declaration.c` answers "How do I declare and initialize an array?"
`03_string_slice.c` answers "How do I represent a string without copying?" This
keeps each exposure short, focused, and memorable.

**Why C?** When Linus Torvalds was asked about C versus newer languages, he said:
*"I still find C to be a much simpler tool. I still like the raw and simple
power of C."* And on the limits of language safety: *"Rust fixes a few easy
bugs that you can make in C, but it does not fix the logic errors. It does not
think for you. When you write incorrect code, the language does not matter."*
(Source: [Open Source Summit India, 2025](https://youtu.be/YKkEe-PxW10))

This course exists for that reason — C isn't here to be trendy. It's the
clearest lens to understand how software actually works. Safety comes from
discipline and understanding, not from the compiler.

---

## The Path (12 groups)

| # | Group | One Question | Project |
|---|-------|-------------|---------|
| 01 | `01_hello/` | How do I write, compile, and run a C program? | madlibs |
| 02 | `02_bitwise/` | How do I manipulate individual bits in integers? | permission_cli |
| 03 | `03_control/` | How do I make decisions and repeat work in C? | number_guess |
| 04 | `04_functions/` | How do I define, call, and organize reusable code? | calculator |
| 05 | `05_strings/` | How do I handle text safely without copying? | fstab_parser |
| 06 | `06_arrays/` | How do I store and process collections of data? | grade_stats |
| 07 | `07_pointers/` | What is a pointer and how do I use one? | array_reverse |
| 08 | `08_dynamic_mem/` | How do I allocate memory at runtime? | dynamic_list |
| 09 | `09_structs/` | How do I group related data into a custom type? | student_db |
| 10 | `10_files/` | How do I read and write files? | csv_reader |
| 11 | `11_advanced/` | How do I use enums, function pointers, and `_Generic`? | generic_sorter |
| 12 | `12_processes/` | How do I launch and control other programs from C? | journal |

Each group has 5–12 concept files, 6–9 exercise solutions, a project
with `BUILD.md`, and a `verify-exercises.sh` script that compiles and
runs every solution to confirm correctness.

---

## Getting Started

Compile any concept file and run it:

```bash
# Start here
gcc -std=c11 -Wall -Wextra -pedantic 01_hello/concept/01_hello_world.c -o /tmp/demo && /tmp/demo
```

Run the exercise solutions and confirm they produce correct output:

```bash
bash 01_hello/exercises/verify-exercises.sh
```

Run the full test suite:

```bash
bash verify.sh
```

For the complete course guide — safe C standard, input patterns, feature flags,
and the Fibonacci study system — see [`COURSE.md`](COURSE.md).

---

## Fibonacci Study System

This course uses **Fibonacci-spaced repetition** to schedule reviews. The
rhythm is 1–2–3–5–8 days between successive reviews of the same unit, following
the Fibonacci sequence. Each unit is seen 5 times total: 1 introduction + 4
reviews at progressively longer intervals, moving knowledge from working memory
into long-term retention.

**Getting started.** Run this script from the course root to generate the study
queue:

```bash
./regenerate_crons.sh
```

This reads `learning_schedule.md` and creates one file per session in
`.fibonacci/queue/`.

**Using the queue.**

```bash
# See what's next
ls .fibonacci/queue/ | head -1

# See how many sessions remain
ls .fibonacci/queue/ | wc -l

# When you finish a session, remove its file
rm .fibonacci/queue/session_001.md
```

See [`learning_schedule.md`](learning_schedule.md) for the full study plan.

---

## License

This course is provided for educational purposes. See individual file headers
for attribution.
