/*
 * File:  05_generic_c11.c
 * Group: 10 — Paradigm Shift: _Generic (C11 type-generic macros)
 *
 * Concept: _Generic — C11's answer to ad-hoc polymorphism
 *
 * _Generic lets you write a macro that selects a different implementation
 * based on the type of its argument, all at compile time.  No runtime
 * dispatch, no function pointer table — the compiler picks the right code
 * path and discards the rest.
 *
 * Syntax:
 *   #define macro(x) _Generic((x), \
 *       int:    fn_int,    \
 *       double: fn_double, \
 *       char*:  fn_str     \
 *   )(x)
 *
 * Shows:
 *   - Type-generic print_val that dispatches on int, double, char*
 *   - A type-generic math wrapper for square
 *   - Dynamic memory (group 09) to store mixed-type results as strings
 *   - snprintf for all string building
 *   - File I/O (group 08) concept via writing to a result buffer
 *
 * Build:  gcc -std=c11 -Wall -Wextra -pedantic 05_generic_c11.c -o 05_generic_c11
 * Run:    ./05_generic_c11
 *
 * NOTE: _Generic is native to C11 — no special flags needed.
 */

#include <stdio.h>
#include <stdlib.h>

/* ---------- individual printer functions ---------- */
static void print_int(int v)    { printf("%d", v); }
static void print_double(double v) { printf("%.2f", v); }
static void print_str(const char *v) { printf("\"%s\"", v); }

/* ---------- type-generic print macro ---------- */
#define print_val(x) _Generic((x),          \
    int:    print_int,                      \
    double: print_double,                   \
    char*:  print_str,                      \
    const char*: print_str                  \
)(x)

/* ---------- square implementations per type ---------- */
static int       square_int(int v)          { return v * v; }
static double    square_double(double v)     { return v * v; }

/* ---------- type-generic square macro ---------- */
#define square(x) _Generic((x),             \
    int:    square_int,                     \
    double: square_double                   \
)(x)

/* ---------- a struct to show integration (group 01) ---------- */
typedef struct {
    char label[32];
    char value[64];
} Result;                                    /* dynamic array of results */

int main(void) {
    /* dynamic array of Results (group 09 + group 01 structs) */
    size_t   n = 4;
    Result  *results = malloc(n * sizeof(Result));
    if (!results) {
        fprintf(stderr, "malloc failed\n");
        return EXIT_FAILURE;
    }

    int       iv  = 7;
    double    dv  = 3.14;
    const char *sv = "hello, C11";

    /* populate results via snprintf (group 07 — safe string building) */
    snprintf(results[0].label, sizeof results[0].label, "int square");
    snprintf(results[0].value, sizeof results[0].value, "%d", square(iv));

    snprintf(results[1].label, sizeof results[1].label, "double square");
    snprintf(results[1].value, sizeof results[1].value, "%.2f", square(dv));

    snprintf(results[2].label, sizeof results[2].label, "print int");
    snprintf(results[2].value, sizeof results[2].value, "see below");

    snprintf(results[3].label, sizeof results[3].label, "print string");
    snprintf(results[3].value, sizeof results[3].value, "see below");

    printf("=== _Generic type dispatch ===\n\n");

    for (size_t i = 0; i < n; i++) {
        printf("  %s: %s\n", results[i].label, results[i].value);
    }

    /* demonstrate the print_val macro dispatching on different types */
    printf("\n  print_val(7)        → ");
    print_val(iv);
    printf("\n  print_val(3.14)     → ");
    print_val(dv);
    printf("\n  print_val(\"hello\") → ");
    print_val(sv);
    printf("\n");

    free(results);
    return EXIT_SUCCESS;
}

/*
 * Thinking in C — Group 10
 *
 * _Generic is compile-time polymorphism without macros hijacking your
 * syntax.  The compiler inspects the controlling expression's type, picks
 * the matching entry, and elides all other branches — zero runtime cost.
 * It's not as ergonomic as C++ templates or Rust generics, but it gives
 * you type-safe generic interfaces in plain C, which is remarkably
 * liberating for libraries, debug helpers, and serialisation routines.
 */
