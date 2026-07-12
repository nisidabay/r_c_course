# SDD Proposal — Fix Exercises in r_c_course

**Status**: Proposed  
**Author**: Hermes Agent (audit-driven)  
**Date**: 2026-07-12  
**Topic key**: `sdd/fix-exercises/proposal`  

---

## 1. Intent

Fix all exercise stubs and solutions in the r_c_course repo so that:
1. Every exercise stub **compiles as-is** (with `-std=c11 -Wall -Wextra -pedantic`) using a placeholder/wrong-value strategy.
2. Every exercise's required output **matches what the concepts taught** — no "leap" challenges requiring untaught techniques.
3. All exercises in a given group use **one consistent stub marker convention** and **one solution file naming convention**.
4. The exercise difficulty ramp is **gradual** (each exercise builds on the previous one *and* the concepts).

---

## 2. Current State (Audit Findings)

### 2.1 Stub Compilability

| Category | Count | Details |
|----------|-------|---------|
| **Stubs that DO compile** | 13 | All 01_hello (6), 02_control/ex_07_challenge, 04_strings/ex_05_zero_copy, 05_arrays/ex_07_challenge (empty body, compiles with -Wno-unused), 07_dynamic_mem/ex_07_challenge (fully implemented!), 08_structs/ex_07_challenge, 09_files/ex_06_challenge, 10_advanced/ex_06_challenge |
| **Stubs that FAIL to compile** | 53 | All others — `/*@*/`, `/* @FILL_ME */`, `// --- your code here ---` in comments break via premature `*/` closing the comment, which cascades into `size_t` not being found in stdio.h |

**Root cause of all compile failures**: The comment describing the stub marker contains the sequence `/* @FILL_ME */` or `/*@*//*@*/` inside a `/* ... */` comment. The first `*/` closes the outer comment, leaving garbage in the C source.

### 2.2 Concept-Exercise Mismatch (The Core Pedagogical Problem)

| Group | Concept teaches | Challenge asks | Gap |
|-------|----------------|----------------|-----|
| **04_strings** | String_Slice, slice_eq, slice_starts_with, slice_take, slice_drop | `is_field_sep()`, `trim_left()`, `next_field()` — field-parsing functions never taught. Student must invent whitespace detection, field scanning logic | **Large** — these functions aren't shown in any concept file |
| **05_arrays** | Declaration, indexing, iteration, multidimensional, sizeof trick, selection sort (concept has exact code) | Median with two-middle averaging as `double` when even count — not in any concept | **Medium** — median computation is new |
| **08_structs** | Struct definition, typedef, member access, arrow operator, structs+fns, struct arrays | Full CRUD loop: fgets loop with vary by count, multiple data types, compute avgs, formatted table | **Large** — loop-input + computed field + formatted table at once |
| **07_dynamic_mem (challenge)** | Heap/stack, malloc, null-check, calloc/realloc, growable array, free/valgrind | Challenge is **fully implemented** (179 lines, no blanks) | **Fully implemented** — nothing for student to do |
| **03_functions** | Defining, return values, pass-by-value, scope, prototypes, exit codes | `/*@*/` placeholders inside function bodies that don't compile | **Mechanical** — stubs broken |

### 2.3 Methodology Inconsistency

| Aspect | Variations found |
|--------|-----------------|
| **Stub markers** (3 variants) | `/*@*/` (02_control, 03_functions, 04_strings, 07_dynamic_mem, 08_structs, 09_files), `/* @FILL_ME */` (05_arrays, 06_pointers_101, 10_advanced), `// --- your code here ---` (10_advanced/ex_06_challenge) |
| **Solution naming** (3 variants) | `ex_NN_xxx_solution.c` (01, 02, 04, 07, 08, 10), `solution_ex_NN_xxx.c` (05), `solutions/` subdirectory with `_solved.c` suffix (03, 06, 09) |
| **Solution location** (2 variants) | Flat alongside stubs (01, 02, 04, 05, 07, 08, 10), in `solutions/` subdirectory (03, 06, 09) |

### 2.4 Exercise Count Issues

| Group | Exercise stubs | README claims | Status |
|-------|---------------|---------------|--------|
| 06_pointers_101 | 6 | "6-7" | OK (lower bound) |
| 09_files | 6 | "6-7" | OK (lower bound) |

Both meet the lower bound; no action needed.

---

## 3. Approach

### 3.1 Phase 1: Standardize All Stub Markers → Compilable `// FILL_ME` pattern

**Current problem**: `/* @FILL_ME */` and `/*@*/` inside `/* ... */` comments break compilation.

**Solution**: Replace ALL `/* @FILL_ME */` and `/*@*/` stub markers with a compilable **sentinel expression** that compiles but produces a wrong/placeholder value.

**Rule (from generate-course skill)**:  
> "Stubs for compiled-language exercises MUST compile as-is with a placeholder/wrong value."

**Concrete patterns**:

```c
// Before (broken):
int result = /*@*/;

// After (compiles, wrong value):
int result = 0;  // FIX ME
```

```c
// Before (broken):
return /*@*/;

// After (compiles, wrong value):
return 0;  // FIX ME
```

```c
// Before (broken, inside comment):
 * Fill in the blanks (marked /* @FILL_ME */) to complete the program.

// After (no broken comment):
 * Fill in the blanks (marked with "FILL ME") to complete the program.
```

**All 53 broken stubs** get this treatment: replace every `/*@*/`, `/* @FILL_ME */`, `// --- your code here ---` with compilable sentinel values (`0`, `NULL`, `""`, `{0}`, etc.) plus a `// FIX ME` comment.

### 3.2 Phase 2: One Solution Convention for All Groups

**Choose**: `ex_NN_xxx_solution.c` (the majority convention — used by 7 of 10 groups already).  

**Groups to migrate**:
- **05_arrays**: `solution_ex_01_array_declaration.c` → `ex_01_array_declaration_solution.c` (and delete the compiled binaries)
- **03_functions, 06_pointers_101, 09_files**: Move from `solutions/ex_NN_xxx_solved.c` → flat `ex_NN_xxx_solution.c`

### 3.3 Phase 3: Fix Concept-Exercise Mismatches

#### 3.3a 04_strings challenge (ex_07_challenge)

**Problem**: Asks for `is_field_sep`, `trim_left`, `next_field` — functions never taught.

**Fix**: Add a concept file `04_strings/concept/07_parsing_fields.c` that demonstrates exactly these three functions on a fstab-like line, then reference it in the challenge. The concept teaches:
- Checking individual chars for whitespace
- Skipping leading whitespace on a String_Slice
- Scanning through a slice to find the next field boundary
- Using slice_take and slice_drop for field extraction

**OR simpler alternative**: Replace the 04_strings challenge with something that only uses the 6 taught String_Slice operations (slice_from_cstring, slice_eq, slice_starts_with, slice_take, slice_drop, slice_from_range, print_slice). Example: a prefix filter that reads lines and filters those starting with a user-specified prefix.

**Recommendation**: Both. Add the concept file and simplify the challenge to only use taught ops, keeping the fstab theme but with more scaffolding.

#### 3.3b 07_dynamic_mem challenge (ex_07_challenge)

**Problem**: Fully implemented, 179 lines, no blanks.

**Fix**: Strip the implementations of `dynarr_create`, `dynarr_push`, `dynarr_pop`, `dynarr_get`, and `dynarr_free` — replace each body with the same sentinel pattern (return 0/1 with `// FIX ME`). The struct definition and main() can stay as-is since they demonstrate the expected output.

**Risk**: The main() function calls the dynarr functions; it must still compile. For `dynarr_push` returning 1 (error), the main loop's test `if (dynarr_push(...) != 0)` will trigger the error path, so we need careful sentinel values. Alternatives: strip main() too and give student a partial scaffold, or keep a simpler version of main().

#### 3.3c 05_arrays challenge (ex_07_challenge)

**Problem**: Empty body (`/* YOUR CODE */`), implements full median program from scratch.

**Fix**: This file already compiles (empty main returns 0). Provide a scaffold with:
- `swap` and `selection_sort` stubs (with compilable sentinels)
- Main scaffold with input loop structure but blank median computation

The median logic (even-count → average two middle as double) should be taught either in a new concept or a comment hint in the challenge.

#### 3.3d 08_structs challenge (ex_07_challenge)

**Problem**: Jumps from basic struct ops to full CRUD system. No intermediate step.

**Fix**: This file already compiles (empty main returns 0). Add scaffolding:
- Student struct definition stub (fill in members)
- Read-one-student helper function stub
- main() with input loop but `// FIX ME` for the average computation and table formatting

**OR**: Add an intermediate exercise ex_07 that reads one student record and prints it, making the current challenge ex_08.

#### 3.3e 03_functions challenge (ex_07_challenge)

**Problem**: All `/*@*/` placeholders, won't compile.

**Fix**: Replace all 11 `/*@*/` markers with compilable sentinels + `// FIX ME`. The function bodies (`factorial`, `is_prime`, `count_divisors`, `print_debug`) get sentinel return values. The main() calls get `0 // FIX ME` or similar.

### 3.4 Phase 4: Update verify-exercises.sh Scripts

Each group's `verify-exercises.sh` script needs updating:
- Point to renamed solution files (for 03, 05, 06, 09)
- Compile ex_NN_xxx.c stubs (they should now compile with warnings about unused vars but zero errors)
- Remove any compiled binaries (like those in 05_arrays/exercises/)

---

## 4. Concrete Outcomes

### 4.1 Files to Modify

| File | Change | Effort |
|------|--------|--------|
| **53 exercise stubs** (.c) | Replace `/*@*/`, `/* @FILL_ME */`, `// YOUR CODE` with compilable sentinel + `// FIX ME` | Large (mechanical) |
| **04_strings/ex_07_challenge.c** | Simplify to only use taught ops | Medium |
| **04_strings/concept/07_parsing_fields.c** | **New file**: teach is_field_sep, trim_left, next_field | Medium |
| **07_dynamic_mem/ex_07_challenge.c** | Strip function bodies, add stubs | Medium |
| **05_arrays/ex_07_challenge.c** | Add scaffolding for swap/sort/median | Small |
| **08_structs/ex_07_challenge.c** | Add scaffolding for struct def + helpers | Small |
| **03_functions/ex_0*_*.c** (7 files) | Replace all `/*@*/` with sentinels | Medium |
| **05_arrays/exercises/*** | Rename solutions, delete compiled binaries | Small |
| **03_functions/exercises/solutions/*** | Move files to flat dir, rename `_solved` → `_solution` | Small |
| **06_pointers_101/exercises/solutions/*** | Same as above | Small |
| **09_files/exercises/solutions/*** | Same as above | Small |
| **verify-exercises.sh** (4 groups) | Update paths for renamed solutions | Small |

### 4.2 Files to Delete

- `05_arrays/exercises/solution_ex_01_array_declaration` (compiled binary)
- `05_arrays/exercises/solution_ex_02_indexing` (compiled binary)
- `05_arrays/exercises/solution_ex_03_iteration` (compiled binary)
- `05_arrays/exercises/solution_ex_04_multidimensional` (compiled binary)
- `05_arrays/exercises/solution_ex_05_sizeof_trick` (compiled binary)
- `05_arrays/exercises/solution_ex_06_sorting` (compiled binary)
- `05_arrays/exercises/solution_ex_07_challenge` (compiled binary)

### 4.3 Success Criteria

1. `bash verify.sh` from course root exits 0 with zero errors.
2. Every `ex_NN_xxx.c` stub file compiles with `gcc -std=c11 -Wall -Wextra -pedantic` with at most warnings about unused variables/parameters.
3. Every `ex_NN_xxx_solution.c` compiles and produces correct output.
4. Every group's `verify-exercises.sh` script passes.
5. No exercise asks students to implement something not demonstrated in its group's concept files.

---

## 5. Risk Assessment

| Risk | Likelihood | Impact | Mitigation |
|------|-----------|--------|------------|
| **Sentinel values cause compile warnings** | High | Medium | Use `0`, `NULL`, empty string — these may generate `-Wunused` warnings but not errors. Add `(void)var;` where needed. |
| **07_dynamic_mem challenge sentinels break main() logic** | Medium | High | Carefully choose sentinels so main() still compiles. May need to simplify main() to only test created/free. |
| **Solutions in solutions/ subdirectory not found by verify script after rename** | Medium | Medium | Update all verify-exercises.sh scripts in Phase 4. Test with `bash verify.sh`. |
| **Concept-Exercise mismatch fix makes group too long** | Low | Low | Adding 1 concept file per group is acceptable. Max 8 concept files per group is fine. |
| **Renaming solution files in 05_arrays breaks verify script** | High | Medium | verify-exercises.sh references `solution_ex_*` — must update to `ex_*_solution`. |
| **Compiled binaries in 05_arrays cause git noise** | Medium | Low | Delete them. They shouldn't be committed. If they are, `git rm` them. |

---

## 6. Recommended Execution Order

1. **Phase 1 first**: Fix all 53 broken stubs to compile. This is the mechanical foundation — everything else depends on compilable stubs.
2. **Phase 2 during Phase 1**: Rename solutions while editing files. Combine rename+content-fix to minimize passes.
3. **Phase 3 after compiling**: Fix concept-exercise mismatches. These are higher-risk and benefit from having compilable stubs already.
4. **Phase 4 last**: Update verify scripts and verify with `bash verify.sh`.

---

## 7. Appendix: Exact Stub Marker Inventory by Group

| Group | Marker | Affected files | Solution location | Solution naming |
|-------|--------|---------------|-------------------|-----------------|
| 01_hello | (none — compiles) | 0 | Flat | `ex_NN_xxx_solution.c` ✓ |
| 02_control | `/*@*/` | ex_01 through ex_06 (6 files) | Flat | `ex_NN_xxx_solution.c` ✓ |
| 03_functions | `/*@*/` | All 7 files | `solutions/` dir | `ex_NN_xxx_solved.c` |
| 04_strings | `/*@*/` | ex_01,02,03,04,06 (5 files; ex_05,07 compile) | Flat | `ex_NN_xxx_solution.c` ✓ |
| 05_arrays | `/* @FILL_ME */` | ex_01 through ex_06 (6 files; ex_07 compiles) | Flat | `solution_ex_NN_xxx.c` |
| 06_pointers_101 | `/* @FILL_ME */` | All 6 files | `solutions/` dir | `_solved.c` |
| 07_dynamic_mem | `/*@*/` | ex_01 through ex_06 (6 files; ex_07 full impl) | Flat | `ex_NN_xxx_solution.c` ✓ |
| 08_structs | `/*@*/` | ex_01 through ex_06 (6 files; ex_07 compiles) | Flat | `ex_NN_xxx_solution.c` ✓ |
| 09_files | `/*@*/` | ex_01 through ex_05 (5 files; ex_06 compiles) | `solutions/` dir | `_solved.c` |
| 10_advanced | `/* @FILL_ME */` and `// YOUR CODE HERE` | ex_01 through ex_05 (5 files; ex_06 compiles) | Flat | `ex_NN_xxx_solution.c` ✓ |
