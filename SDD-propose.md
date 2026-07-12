# SDD Proposal — Standardize r_c_course (SDD-PROPOSE Phase)

**Status**: Proposed  
**Author**: Hermes Agent (subagent)  
**Date**: 2026-07-12  
**Topic key**: `sdd/standardize-r_c_course/proposal`

---

## 1. Intent

Standardize **every** `.c` file in the r_c_course repo (50+ concept files, 60+ exercise files, 10 project files, 10 verify scripts) to one unambiguous set of patterns. Zero ambiguity. One pattern for everything, repeated identically in every file.

**The three pillars (from Carlos):**

1. **INPUT**: `fgets` → check NULL → `strcspn(buf, "\n")` strip newline → `strtol` with `errno=0` + `ERANGE` + `endptr == buf || *endptr != '\0'` → `fprintf(stderr)` on error → `return EXIT_FAILURE`. **NO** `sscanf`. **NO** `atoi`. **NO** `consume_remaining`.
2. **FILES**: `fopen` → `if (!fp) { perror(...); return EXIT_FAILURE; }`. Always. No variants.
3. **MEMORY**: `malloc` → `if (!ptr) { perror(...); return 1; }`. Always.
4. **EXIT CODES**: `EXIT_SUCCESS` / `EXIT_FAILURE` from `<stdlib.h>`. Not raw `0`/`1` in `main()`. (Helper functions may still return `0`/`1` as error codes.)
5. **ERROR OUTPUT**: `fprintf(stderr, ...)` or `perror(...)`. Never `printf` for errors.

---

## 2. Scope: What Must Change

### 2.1 Pattern Violations Found (by Category)

#### A. `sscanf` Usage → Must Become `strtol` (EVERY instance)

| File | Lines | Current Pattern |
|------|-------|-----------------|
| `01_hello/exercises/ex_06_challenge_solution.c` | 41, 56 | `sscanf(str, "%d", &var)` |
| `01_hello/exercises/ex_06_challenge.c` | 32, 36 | `sscanf` (commented out) |
| `02_control/exercises/ex_01_if_else.c` | 28 | `fgets + sscanf` |
| `02_control/exercises/ex_01_if_else_solution.c` | 20 | `fgets + sscanf` |
| `02_control/exercises/ex_02_while.c` | 25 | `fgets + sscanf` |
| `02_control/exercises/ex_02_while_solution.c` | 20 | `fgets + sscanf` |
| `02_control/exercises/ex_03_for.c` | 27 | `fgets + sscanf` |
| `02_control/exercises/ex_03_for_solution.c` | 21 | `fgets + sscanf` |
| `02_control/exercises/ex_04_logical.c` | 29 | `fgets + sscanf` |
| `02_control/exercises/ex_04_logical_solution.c` | 22 | `fgets + sscanf` |
| `02_control/exercises/ex_05_comparisons.c` | 34 | `fgets + sscanf` |
| `02_control/exercises/ex_05_comparisons_solution.c` | 20 | `fgets + sscanf` |
| `02_control/exercises/ex_06_break_continue.c` | 30 | `fgets + sscanf` |
| `02_control/exercises/ex_06_break_continue_solution.c` | 23 | `fgets + sscanf` |
| `02_control/exercises/ex_07_challenge_solution.c` | 20 | `fgets + sscanf` |
| `02_control/exercises/ex_07_challenge.c` | 35 (comment only) | references sscanf |
| `02_control/project/number_guess.c` | 9 | comment references sscanf (actually uses strtol) |
| `03_functions/concept/06_exit_codes.c` | 32 | `sscanf(input, "%d", &value)` |
| `03_functions/exercises/ex_01_defining.c` | 42 | `fgets + sscanf` |
| `03_functions/exercises/solutions/ex_01_defining_solved.c` | 32 | `fgets + sscanf` |
| `03_functions/exercises/solutions/ex_02_return_values_solved.c` | 39 | `fgets + sscanf` |
| `03_functions/exercises/ex_03_pass_by_value.c` | 46 | `fgets + sscanf` |
| `03_functions/exercises/solutions/ex_03_pass_by_value_solved.c` | 33 | `fgets + sscanf` |
| `03_functions/exercises/solutions/ex_04_scope_solved.c` | 30 | `fgets + sscanf` |
| `03_functions/exercises/ex_05_prototypes.c` | 42 | `fgets + sscanf` |
| `03_functions/exercises/solutions/ex_05_prototypes_solved.c` | 32 | `fgets + sscanf` |
| `03_functions/exercises/solutions/ex_07_challenge_solved.c` | 28 | `fgets + sscanf` |
| `05_arrays/project/grade_stats.c` | 28 | `sscanf(line, "%d", &val)` |
| `05_arrays/exercises/solution_ex_07_challenge.c` | 48 | `sscanf(buf, "%d", &val)` |
| `06_pointers_101/project/array_reverse.c` | 91 | `sscanf(line, "%d", &val)` |
| `07_dynamic_mem/project/dynamic_list.c` | 143 | `sscanf(line, "%63[^,],%15s", ...)` |
| `08_structs/project/student_db.c` | 59, 68, 113 | `sscanf(buf, "%d", &var)` |
| `08_structs/exercises/ex_07_challenge_solution.c` | (stub, not examined) | check for sscanf |

**Total: ~35+ files** with sscanf that must become strtol.

#### B. `return 0` / `return 1` Instead of EXIT_SUCCESS / EXIT_FAILURE in `main()`

Every concept file in 20+ locations uses `return 0` in `main()`. Many use `return 1` instead of `EXIT_FAILURE`. See audit in Phase 3 for full list.

**Key finding**: The concept file `03_functions/concept/06_exit_codes.c` **teaches** using `EXIT_SUCCESS`/`EXIT_FAILURE` but then the functions inside return raw `0`/`1`. The teaching concept itself is inconsistent.

#### C. `consume_remaining` Pattern Must Be REMOVED

The `consume_remaining()` function appears in:
- `01_hello/concept/05_simple_input.c` — uses `strcspn` + `consume_remaining` + `strtol` (almost correct but has consume_remaining)
- `01_hello/exercises/ex_05_input_solution.c` — `consume_remaining`
- `01_hello/exercises/ex_06_challenge_solution.c` — `consume_remaining`
- `01_hello/project/madlibs.c` — `read_input` helper (no consume_remaining in the helper itself, but the `read_input` design is good)
- `03_functions/project/calculator.c` — `consume_remaining`
- `08_structs/exercises/ex_07_challenge_solution.c` — `consume_remaining`

**The standardized pattern**: `fgets` + `strcspn(buf, "\n")` strip newline. The newline is always present if input fits (and we use generously-sized buffers). If truncation happens, the next `fgets` reads the remainder — but in a practice course with small prompts, truncation is unlikely and the `strcspn` approach handles it gracefully. Carlos explicitly said: **NO `consume_remaining`**.

#### D. `printf` for Error Messages

- `07_dynamic_mem/exercises/ex_07_challenge.c` — `printf("Pop error: array is empty\n");` (×2)
- `03_functions/project/calculator.c` — `printf("Error: division by zero...");` (×2)
- `07_dynamic_mem/exercises/ex_07_challenge_solution.c` — same pattern

All must become `fprintf(stderr, ...)`.

#### E. Broken Exercise Stubs (Don't Compile)

From the existing SDD-fix-exercises.md audit, **53 exercise stubs fail to compile** because of `/*@*/` and `/* @FILL_ME */` markers inside `/* ... */` comments. These must be replaced with compilable sentinel values + `// FIX ME` comments.

#### F. Concept-Exercise Mismatches

1. **04_strings challenge** (`ex_07_challenge.c`): Asks students to implement `is_field_sep`, `trim_left`, `next_field` — field-parsing functions **never taught** in any concept file. Must either add a concept file or redesign the challenge.
2. **07_dynamic_mem challenge** (`ex_07_challenge.c`): **Fully implemented** (179 lines, no blanks for students). Must strip function bodies into stubs.
3. **05_arrays challenge**: Empty body that compiles but provides no scaffold. Needs swap/sort/median scaffold.
4. **08_structs challenge**: Empty body. Needs scaffold.
5. **03_functions challenge**: 11 `/*@*/` placeholders, doesn't compile.

#### G. Missing Concept Files

The following topics exist in `~/temp/C_temp/` as reference-quality code but are **not yet in the course** as concept files:

| Temp File | Topic | Where It Should Go | Priority |
|-----------|-------|-------------------|----------|
| `real_swap.c` | Swap via pointers (EXIT_SUCCESS/FAILURE) | `06_pointers_101/concept/` | **High** — fills gap before `04_pointers_params` |
| `swap_value.c` | Swap by value (contrast) | `06_pointers_101/concept/` | **High** — paired with real_swap |
| `pointer_comparison.c` | Pointer arithmetic with while loop (`ptr < end`) | `06_pointers_101/concept/` | **High** — teaches pointer comparison idiom |
| `const_pointer_to_data.c` | `int *const p` | `06_pointers_101/concept/` | **Medium** — important for API design |
| `pointer_to_const_data.c` | `const int *p` | `06_pointers_101/concept/` | **Medium** — important for API design |
| `double_pointer.c` | `int **p` | `06_pointers_101/concept/` | **Medium** — needed for `strtol` endptr understanding |
| `check_endian.c` | Endianness via `*(char*)&num` | `06_pointers_101/concept/` | **Low** — nice-to-have |
| `strtol.c` | Full strtol validation (errno, ERANGE, endptr) | `03_functions/concept/` or `06_pointers_101/concept/` | **Critical** — the canonical strtol example |
| `validate_int.c` | `is_valid_int` helper using strtol | `03_functions/concept/` | **High** — reusable validation helper |
| `print_experiment.c` | printf wrapper with error checking | `03_functions/concept/` | **Medium** — teaches return-value checking |
| `strtok.c` | strtok splitting | `04_strings/concept/` | **Medium** — for 10_advanced tok concepts |
| `generic_array_printing.c` | _Generic + const void* | `10_advanced/concept/` | **Low** — overlaps existing generic concept |
| `lenstr.c` | Manual strlen implementation | `04_strings/concept/` | **Low** — already implicitly covered |
| `fopen_ex.c` | fopen + fprintf + perror + fclose | `09_files/concept/` | **High** — better example than current |
| `opening_files.c` | fopen NULL check + perror | `09_files/concept/` | **High** — simpler focused example |
| `fgets_sscanf.c` | Unified input pattern | `01_hello/concept/` (or replace 05) | **High** — must convert sscanf→strtol first |

**Key insight**: The `strtol` concept is the most critical missing piece. Currently, `strtol` is **not formally taught** anywhere as a concept — it's introduced ad-hoc in `01_hello/concept/05_simple_input.c` with the disclaimer "don't worry about pointers" and in `02_control/project/number_guess.c`. The full validation pattern (errno=0, ERANGE, endptr checks) is never taught in a dedicated concept file.

---

## 3. The One True Pattern (Must Be in EVERY File)

### 3.1 Integer Input (THE standard pattern)

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

**Rationale**: This pattern is:
- **Unambiguous**: exactly one way to read an integer
- **Safe**: catches every error mode (EOF, overflow, no digits, trailing garbage)
- **Self-contained**: no helper functions, no `consume_remaining`
- **Teach once, use everywhere**: after concept 03 (pointers/endptr), students understand why it works

### 3.2 File Opening

```c
FILE *fp = fopen("filename", "r");
if (fp == NULL) {
    perror("fopen");
    return EXIT_FAILURE;
}
```

### 3.3 Memory Allocation

```c
int *arr = malloc(n * sizeof(*arr));
if (arr == NULL) {
    perror("malloc");
    return EXIT_FAILURE;
}
```

### 3.4 Error Output

- Errors: `fprintf(stderr, "Error: ...\n");` or `perror("operation");`
- Success messages: `printf(...)` or `puts(...)`
- NEVER `printf("Error: ...")` for errors

---

## 4. Files to Modify (Full Inventory)

### 4.1 Phase 1: Fix Broken Stubs (53 files)

All 53 exercise stubs with `/*@*/`, `/* @FILL_ME */`, or `// --- your code here ---` must be replaced with compilable sentinel values + `// FIX ME`. See `SDD-fix-exercises.md` for exact inventory.

### 4.2 Phase 2: sscanf → strtol Conversion (~35 files)

All files listed in §2.1A above. Additionally update all comments that say "use fgets + sscanf" to say "use fgets + strtol".

### 4.3 Phase 3: return 0/1 → EXIT_SUCCESS/EXIT_FAILURE in main() (30+ concept files)

Every concept file in groups 01, 02, 04, 05, 06, 07, 08, 09 that uses `return 0` in `main()` must change to `return EXIT_SUCCESS`. Files using `return 1` in `main()` must change to `return EXIT_FAILURE`.

**Exception**: Helper functions that return `0`/`1` as error codes (not from `main()`) can stay as-is — `EXIT_SUCCESS`/`EXIT_FAILURE` are for `main()` only.

### 4.4 Phase 4: Remove `consume_remaining` (6+ files)

Replace `consume_remaining()` with `buf[strcspn(buf, "\n")] = '\0'` pattern. The newline stripping is all that's needed when using properly sized buffers.

### 4.5 Phase 5: Fix Error Output (4+ files)

Convert `printf("Error: ...")` to `fprintf(stderr, "Error: ...\n")` or `perror(...)`.

### 4.6 Phase 6: Fix Concept-Exercise Mismatches (5 files)

1. **04_strings challenge**: Add `07_parsing_fields.c` concept file OR redesign challenge to only use taught operations
2. **07_dynamic_mem challenge**: Strip function bodies, add stubs
3. **05_arrays challenge**: Add scaffold with swap/sort/median stubs
4. **08_structs challenge**: Add scaffold with struct def + helper stubs
5. **03_functions challenge**: Replace `/*@*/` with sentinels

### 4.7 Phase 7: Add Missing Concept Files (16 files from temp)

Convert the following temp files into standardized course concept files:

| New File | From Temp | Standardize? |
|----------|-----------|-------------|
| `03_functions/concept/07_strtol_validation.c` | `strtol.c` | sscanf→strtol already, ensure EXIT_SUCCESS/FAILURE |
| `03_functions/concept/08_validate_int.c` | `validate_int.c` | Ensure EXIT_SUCCESS/FAILURE, add full errno pattern |
| `03_functions/concept/09_print_wrapper.c` | `print_experiment.c` | Already uses EXIT_SUCCESS/FAILURE ✓ |
| `06_pointers_101/concept/06_real_swap.c` | `real_swap.c` | Already uses EXIT_SUCCESS/FAILURE ✓ |
| `06_pointers_101/concept/07_swap_value.c` | `swap_value.c` | Already uses EXIT_SUCCESS/FAILURE ✓ |
| `06_pointers_101/concept/08_pointer_comparison.c` | `pointer_comparison.c` | Fix: no EXIT_SUCCESS in main |
| `06_pointers_101/concept/09_const_pointer.c` | `const_pointer_to_data.c` | Uses EXIT_SUCCESS ✓ |
| `06_pointers_101/concept/10_pointer_to_const.c` | `pointer_to_const_data.c` | Uses EXIT_SUCCESS ✓ |
| `06_pointers_101/concept/11_double_pointer.c` | `double_pointer.c` | Uses EXIT_SUCCESS ✓ but has scanf! |
| `06_pointers_101/concept/12_check_endian.c` | `check_endian.c` | Fix: no EXIT_SUCCESS, `int main()` not `int main(void)` |
| `04_strings/concept/07_strtok.c` | `strtok.c` | Fix: no EXIT_SUCCESS |
| `04_strings/concept/08_generic_array_print.c` | `generic_array_printing.c` | Fix: no EXIT_SUCCESS |
| `04_strings/concept/09_lenstr.c` | `lenstr.c` | Fix: no EXIT_SUCCESS |
| `09_files/concept/06_fopen_example.c` | `fopen_ex.c` | Already uses EXIT_SUCCESS/FAILURE ✓ |
| `09_files/concept/07_opening_files.c` | `opening_files.c` | Already uses EXIT_SUCCESS/FAILURE ✓ |

### 4.8 Phase 8: Fix Project Files (10 files)

| File | Issues |
|------|--------|
| `01_hello/project/madlibs.c` | `return 1` → `EXIT_FAILURE`, `exit(1)` → `exit(EXIT_FAILURE)`, `return 0` → `return EXIT_SUCCESS`, no `consume_remaining` needed |
| `02_control/project/number_guess.c` | Uses strtol ✓, but `return 0` → `EXIT_SUCCESS`; `printf("Goodbye!")` fine |
| `03_functions/project/calculator.c` | `consume_remaining` → remove, `printf("Error")` → `fprintf(stderr, ...)` for division-by-zero, `return 0` → `EXIT_SUCCESS` |
| `05_arrays/project/grade_stats.c` | `sscanf` → `strtol`, `#include <stdlib.h>` already for EXIT_FAILURE, `return 0` → `EXIT_SUCCESS` |
| `06_pointers_101/project/array_reverse.c` | `sscanf` → `strtol`, trim newline via `strcspn` not `strlen` manual |
| `07_dynamic_mem/project/dynamic_list.c` | `sscanf` → `strtol`/manual parse |
| `08_structs/project/student_db.c` | 3× `sscanf` → `strtol`, `return 0` → `EXIT_SUCCESS`, `clear_stdin` → remove (use fgets) |
| `09_files/project/csv_reader.c` | `return 1` → `EXIT_FAILURE` (×3), `return 0` → `EXIT_SUCCESS` |
| `10_advanced/project/generic_sorter.c` | Check for sscanf/exit code issues |

### 4.9 Phase 9: Concept File Standardization (50 files)

Every existing concept file needs to be audited and updated for:
1. `return 0` in `main()` → `return EXIT_SUCCESS`
2. `return 1` in `main()` → `return EXIT_FAILURE`
3. `sscanf` → `strtol` (concept `03_functions/06_exit_codes.c` is the only concept with sscanf)
4. `// Thinking in C:` footer (most already have this ✓)
5. `int main(void)` signature (most already correct ✓)
6. `consume_remaining` (only `01_hello/concept/05_simple_input.c` has it)

---

## 5. Execution Order

```
Phase 1: Fix all 53 broken exercise stubs (foundation — everything else depends on compiling)
    ↓
Phase 2: Convert all sscanf → strtol (35+ files, mechanical but high-impact)
    ↓
Phase 3: Convert return 0/1 → EXIT_SUCCESS/EXIT_FAILURE (30+ concept files, mechanical)
    ↓
Phase 4: Remove consume_remaining from all files (6+ files)
    ↓
Phase 5: Fix error output (printf → fprintf(stderr) / perror) (4+ files)
    ↓
Phase 6: Add missing concept files (16 files from ~/temp/C_temp/)
    ↓
Phase 7: Fix concept-exercise mismatches (5 exercise files)
    ↓
Phase 8: Standardize project files (10 files)
    ↓
Phase 9: Final audit — run verify.sh, fix any remaining issues
```

**Rationale for this order**:
- Phase 1 first because everything depends on stubs compiling
- Phase 2-5 are mechanical pattern replacements — do them next while the codebase is fresh
- Phase 6 adds new material (concepts) that the exercises reference
- Phase 7 fixes mismatches after concepts are in place
- Phase 8 standardizes projects last (they're the most complex files)
- Phase 9 is the final verification pass

---

## 6. Success Criteria

1. `bash verify.sh` from course root exits 0 with zero errors.
2. Every `.c` file compiles with `gcc -std=c11 -Wall -Wextra -pedantic`.
3. **Zero** `sscanf` usage remains in any `.c` file (unless it's a comment about the old pattern).
4. **Zero** `atoi` usage remains.
5. **Zero** `consume_remaining` function definitions remain.
6. **Every** `main()` returns `EXIT_SUCCESS` or `EXIT_FAILURE`, never raw `0`/`1`.
7. **Every** `fopen` is followed by `if (!fp) { perror(...); return EXIT_FAILURE; }`.
8. **Every** `malloc`/`calloc`/`realloc` is followed by `if (!ptr) { perror(...); ... }`.
9. **Every** error message goes to `stderr`, not `stdout`.
10. Every exercise challenge only requires concepts actually taught in its group's concept files.
11. Exercise stubs compile with compilable sentinel values (even if they produce wrong output).

---

## 7. Risk Assessment

| Risk | Likelihood | Impact | Mitigation |
|------|-----------|--------|------------|
| Mass sscanf→strtol conversion breaks files | High | High | Verify each file compiles after conversion. Use verify.sh as safety net. |
| 04_strings challenge redesign is complex | Medium | Medium | Option A: add `07_parsing_fields.c` concept. Option B: replace challenge with prefix filter. A+B is safest. |
| Some concept files don't use `#include <stdlib.h>` for EXIT_SUCCESS | High | Low | Add the include. Safe. |
| `consume_remaining` removal breaks sequential fgets | Low | Medium | With properly-sized buffers (64-256) and `strcspn` stripping, the newline is consumed by fgets. Only edge case: user types >256 chars, which is unlikely in this course. |
| `double_pointer.c` from temp uses `scanf` not `fgets+strtol` | High | Low | Convert it. Known issue. |
| Project files are complex and have multiple issues | High | Medium | Do projects last (Phase 8) when patterns are well-established. |

---

## 8. Summary of Effort

| Phase | Description | Files Affected | Approx. Effort |
|-------|-------------|---------------|----------------|
| 1 | Fix broken stubs | 53 | Large (mechanical) |
| 2 | sscanf → strtol | 35 | Large (mechanical + careful validation) |
| 3 | return 0/1 → EXIT_SUCCESS/FAILURE | 30+ | Medium (mechanical) |
| 4 | Remove consume_remaining | 6 | Small (mechanical) |
| 5 | Fix error output | 4 | Small (mechanical) |
| 6 | Add missing concept files | 16 (new) | Large (content creation) |
| 7 | Fix concept-exercise mismatches | 5 | Medium (design + implementation) |
| 8 | Standardize project files | 10 | Medium (complex files) |
| 9 | Final audit + verify.sh | All | Medium (verification) |

---

## 9. Key Decision: Where to Teach strtol

**Question**: Which group should teach the full `strtol` validation pattern?

**Recommendation**: **Group 03 (Functions)** as concept `07_strtol_validation.c`. Rationale:
- Group 01 already introduces `strtol` in `05_simple_input.c` with "don't worry about pointers"
- Group 02 uses `strtol` in `number_guess.c` with basic validation
- Group 03 teaches exit codes and return values — the full `strtol` pattern with `errno`, `ERANGE`, and `endptr` validation fits naturally here
- Group 06 teaches pointers, which explains `endptr` at a deeper level — the Group 03 concept can reference "we'll cover pointers in depth later"

**Alternative**: Group 06, after pointer basics. This is more pedagogically correct (students understand `endptr` as a pointer-to-pointer) but delays the full pattern until later.

**Compromise**: Introduce the pattern in Group 03 as a "pattern to memorize now, understand later" concept, then revisit it in Group 06 after pointer-to-pointer is taught.

---

## 10. Appendix: Exact Temp File Standardization Needed

| Temp File | Already Uses EXIT_SUCCESS/FAILURE? | Has sscanf/scanf? | Has consume_remaining? | Has return 0 in main? | Action |
|-----------|------|------|------|------|--------|
| `fgets_sscanf.c` | ✓ (EXIT_SUCCESS/FAILURE) | Uses strtol already ✓ | ✗ (none) | ✗ | Good, but rename and add "// Thinking in C:" footer |
| `strtol.c` | ✓ | ✗ (clean) | ✗ | ✗ | Ready to add as concept 07 in group 03 |
| `validate_int.c` | ✗ (return 0/1) | ✗ (strtol) | ✗ | `return 0`, `return 1` | Add includes, fix returns |
| `real_swap.c` | ✓ | ✗ | ✗ | ✗ | Ready, add footer |
| `swap_value.c` | ✓ | ✗ | ✗ | ✗ | Ready, add footer |
| `pointer_comparison.c` | ✗ (no EXIT_SUCCESS/FAILURE at all) | ✗ | ✗ | `return 0`, `return 1` | Fix includes + returns |
| `const_pointer_to_data.c` | ✓ | ✗ | ✗ | ✗ | Ready, add footer |
| `pointer_to_const_data.c` | ✓ | ✗ | ✗ | ✗ | Ready, add footer |
| `double_pointer.c` | ✓ (but has `scanf`) | `scanf` | ✗ | ✗ | Convert scanf→fgets+strtol |
| `check_endian.c` | ✗ | ✗ | ✗ | `return 0` | Fix main signature + EXIT_SUCCESS |
| `strtok.c` | ✗ | ✗ | ✗ | `return 0` (×2) | Add EXIT_SUCCESS |
| `generic_array_printing.c` | ✗ | ✗ | ✗ | `return 0` | Add EXIT_SUCCESS |
| `lenstr.c` | ✗ | ✗ | ✗ | `return 0` | Add EXIT_SUCCESS, add footer |
| `print_experiment.c` | ✓ | ✗ | ✗ | ✗ | Ready, add footer |
| `fopen_ex.c` | ✓ | ✗ | ✗ | ✗ | Ready, add footer |
| `opening_files.c` | ✓ | ✗ | ✗ | ✗ | Ready, add footer |

---

## 11. Changes to README.md

The README at `/home/nisidabay/r_c_course/README.md` currently says:

> "All input uses `fgets` + `sscanf`."
> "Banned functions include `strcpy`, `strcat`, `sprintf`, `scanf`, `atoi`, and `atof`."

After standardization, this must change to:

> "All input uses `fgets` + `strtol` (with full `errno`/`endptr` validation)."
> "Banned functions include `strcpy`, `strcat`, `sprintf`, `scanf`, `sscanf`, `atoi`, and `atof`."

Also update the Safe C Standard table (line 147): `scanf` → `fgets + sscanf` should become `scanf`/`sscanf` → `fgets + strtol`.

---

## 12. Reference: Current State of Concept Files by Group

| Group | Concept Files | Already Use EXIT_SUCCESS? | Have sscanf? | Notes |
|-------|--------------|--------------------------|-------------|-------|
| 01_hello | 5 | No (all return 0) | No | 05_simple_input uses consume_remaining |
| 02_control | 6 | No (all return 0) | No | Mostly clean |
| 03_functions | 6 | 06_exit_codes uses EXIT_SUCCESS/FAILURE ✓ | 06_exit_codes has sscanf | 01-05 return 0 |
| 04_strings | 6 | No (all return 0) | No | Clean |
| 05_arrays | 6 | No (all return 0) | No | Clean |
| 06_pointers_101 | 5 | No (all return 0) | No | Missing pointer comparison, const, double-pointer concepts |
| 07_dynamic_mem | 6 | No (most return 0, some return 1) | No | Clean otherwise |
| 08_structs | 6 | No (all return 0) | No | Clean |
| 09_files | 5 | No (all return 0) | No | Clean |
| 10_advanced | 5 | No (all return 0) | No | Clean |
