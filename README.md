# Modern C — Safe tools for the Linux sysadmin

Learn C the way you'll use it: to write CLI tools for Linux.

```bash
git clone https://github.com/yourname/r_c_course.git
cd r_c_course

# Start here
gcc -std=c11 -Wall -Wextra -pedantic -Werror -o /tmp/hello \
    01_hello_world/concept/01_hello.c && /tmp/hello
```

## The Path (8 modules)

| Module | Title | Key Concepts | Project |
|--------|-------|--------------|---------|
| 01 | Hello, World | Compilation, `printf`, return values, basic types, format strings | `sysinfo` |
| 02 | Control Flow | `if`/`else`, `switch`, `for`, `while`, functions, scope | `divider` |
| 03 | Arrays & Strings | Arrays, C strings, `strlen`/`strcmp`, pointer basics, string copy | `grep-lite` |
| 04 | Numbers | Integer types, `size_t`, signed/unsigned, overflow, `strtol` | `calc` |
| 05 | Dynamic Memory | `malloc`, `realloc`, `free`, Valgrind, struct allocation | `uniq` |
| 06 | File I/O | `fopen`/`fclose`, `fgets`, `stat`, `readdir`, `String_Slice` | `wc-lite` |
| 07 | Processes | `fork`/`exec`, `waitpid`, `popen`, signals, env vars | `runit` |
| 08 | Organization | Makefiles, unity build, `static`/`extern`, preprocessor | `todo` |

## Course Conventions

- **C11 strict**: `-std=c11 -Wall -Wextra -pedantic -Werror`
- **`size_t`** for lengths and indices
- **`EXIT_SUCCESS` / `EXIT_FAILURE`**, never raw numbers
- **`const` on the left**: `const int *`
- **`fgets()`** for input, **`snprintf()`** for string construction
- **`perror()`** for system call errors
- **`static` by default** on internal functions
- Every file compiles standalone: `gcc -std=c11 -Wall -Wextra -pedantic -Werror file.c`

## Feature Flags

Some POSIX functions require explicit feature-test macros before `#include`:

```c
#define _POSIX_C_SOURCE 200809L   /* for getopt_long, gethostname, fileno */
#define _GNU_SOURCE                /* for getopt_long (glibc shortcut) */
```

These are explained in the files that use them.

## Quick Build

```bash
# Any concept file
gcc -std=c11 -Wall -Wextra -pedantic -Werror -o /tmp/t concept_file.c && /tmp/t

# Any project
cd 03_arrays_strings/project && make run

# Verify everything
./verify.sh
```

## Fibonacci Study System

This course uses a **spaced-repetition schedule** based on the Fibonacci sequence (1-2-3-5-8 day intervals).

See `learning_schedule.md` for the full plan, then run:

```bash
./regenerate_crons.sh   # Set up cron reminders
ls .fibonacci/queue/     # See what to study today
rm session_NNN.md        # Mark a session complete
```
