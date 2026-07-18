# Learning Schedule — Fibonacci Study Plan

Each unit is introduced once and reviewed 4 times at Fibonacci intervals
(2, 3, 5, and 8 days after the previous session for that unit).

| Day | # | Unit | Activity |
|-----|---|------|----------|
| 1 | 1 | 01_hello | Print and run your first C program |
| 2 | 2 | 01_hello | Review: modify the greeting, try different data types |
| 3 | 3 | 01_hello | Review: add arithmetic, format output |
| 5 | 4 | 01_hello | Review: add user input with fgets + strtol |
| 8 | 5 | 01_hello | Review: compile with -Wall -Wextra -pedantic, fix warnings |
| 9 | 6 | 02_bitwise | Print integers in binary, understand bitwise NOT (~) |
| 10 | 7 | 02_bitwise | Review: combine AND, OR, XOR to mask and toggle bits |
| 11 | 8 | 02_bitwise | Review: shift operations, pack/unpack bit fields |
| 13 | 9 | 02_bitwise | Review: build a bitmask from multiple flags |
| 16 | 10 | 02_bitwise | Review: bitwise calculator — parse and compute expressions |
| 17 | 11 | 03_control | Branch with if/else, loop with while and for |
| 18 | 12 | 03_control | Review: combine logical ops, comparison chains |
| 19 | 13 | 03_control | Review: break/continue for loop control |
| 21 | 14 | 03_control | Review: nested loops, early-exit patterns |
| 24 | 15 | 03_control | Review: number guessing game — full control flow |
| 25 | 16 | 04_functions | Define functions, return values, parameters |
| 26 | 17 | 04_functions | Review: scope, prototypes, header ordering |
| 27 | 18 | 04_functions | Review: exit codes, strtol validation |
| 29 | 19 | 04_functions | Review: validate_int wrapper, print wrapper |
| 32 | 20 | 04_functions | Review: assert for invariants, errno for system errors |
| 33 | 21 | 05_strings | Represent strings with char pointers, understand null terminators |
| 34 | 22 | 05_strings | Review: string slices, zero-copy subsections |
| 35 | 23 | 05_strings | Review: safe string building with snprintf |
| 37 | 24 | 05_strings | Review: array of pointers, strtok for parsing |
| 40 | 25 | 05_strings | Review: length check without strlen, string utilities |
| 41 | 26 | 06_arrays | Declare and index arrays, iterate with loops |
| 42 | 27 | 06_arrays | Review: multidimensional arrays, row-major layout |
| 43 | 28 | 06_arrays | Review: sizeof trick, array bounds discipline |
| 45 | 29 | 06_arrays | Review: sorting arrays with qsort |
| 48 | 30 | 06_arrays | Review: grade statistics project — full array processing |
| 49 | 31 | 07_pointers | Take addresses with &, dereference with * |
| 50 | 32 | 07_pointers | Review: null pointers, pointers as parameters |
| 51 | 33 | 07_pointers | Review: arrays decay to pointers, pointer arithmetic |
| 53 | 34 | 07_pointers | Review: swap via pointers, const correctness |
| 56 | 35 | 07_pointers | Review: double pointers, endianness detection |
| 57 | 36 | 08_dynamic_mem | Heap vs stack, malloc and NULL check |
| 58 | 37 | 08_dynamic_mem | Review: calloc, realloc, growable arrays |
| 59 | 38 | 08_dynamic_mem | Review: free, valgrind for leak detection |
| 61 | 39 | 08_dynamic_mem | Review: dynamic list project — full CRUD |
| 64 | 40 | 08_dynamic_mem | Review: realloc failure, safe cleanup patterns |
| 65 | 41 | 09_structs | Define structs, typedef, access members |
| 66 | 42 | 09_structs | Review: arrow operator, structs as function parameters |
| 67 | 43 | 09_structs | Review: arrays of structs, sorting by field |
| 69 | 44 | 09_structs | Review: unions — type punning and memory sharing |
| 72 | 45 | 09_structs | Review: student database project — struct + file I/O |
| 73 | 46 | 10_files | Open files with fopen, read/write text |
| 74 | 47 | 10_files | Review: fclose, cleanup on error |
| 75 | 48 | 10_files | Review: perror, error messages to stderr |
| 77 | 49 | 10_files | Review: file operations — rename, remove, temp files |
| 80 | 50 | 10_files | Review: CSV reader project — parse structured files |
| 81 | 51 | 11_advanced | Enums with switch, function pointers |
| 82 | 52 | 11_advanced | Review: qsort with comparison function pointers |
| 83 | 53 | 11_advanced | Review: strtok_r (reentrant), _Generic dispatch |
| 85 | 54 | 11_advanced | Review: generic array print, variadic functions |
| 88 | 55 | 11_advanced | Review: generic sorter project — pluggable comparators |
| 89 | 56 | 12_processes | Fork, exec, waitpid — how Bash runs commands |
| 90 | 57 | 12_processes | Review: execlp, execvp, PATH resolution |
| 91 | 58 | 12_processes | Review: popen, system — when to (not) use them |
| 93 | 59 | 12_processes | Review: pipes, dup2, inter-process communication |
| 96 | 60 | 12_processes | Review: getenv, getopt, sqlite3, signal handling |

---

## Summary

- **60 sessions** total (12 units × 5 sessions each)
- **96 days** to complete the full cycle
- Each session is ~15–30 minutes of focused work
- Run `./regenerate_crons.sh` to create the session queue
- Check `ls .fibonacci/queue/` to see what's next
- `rm .fibonacci/queue/session_NNN.md` marks a session complete
