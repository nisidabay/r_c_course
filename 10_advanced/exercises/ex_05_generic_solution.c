/*
 * ex_05_generic_solution.c
 * Group 10 — Advanced
 * Exercise 05: _Generic (C11 type-generic macros) — SOLUTION
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_int(int v)         { printf("int:%d", v); }
static void print_double(double v)   { printf("dbl:%.1f", v); }
static void print_str(const char *v) { printf("str:\"%s\"", v); }

#define print_val(x) _Generic((x),                              \
    int:         print_int,                                     \
    double:      print_double,                                  \
    char*:       print_str,                                     \
    const char*: print_str                                      \
)(x)

static int       square_int(int v)       { return v * v; }
static double    square_double(double v) { return v * v; }

#define square(x) _Generic((x),         \
    int:    square_int,                 \
    double: square_double               \
)(x)

typedef struct {
    char label[32];
    char value[64];
} Result;

int main(void) {
    int       iv  = 5;
    double    dv  = 2.5;
    const char *sv = "C11 generic";

    int    sq_i = square(iv);
    double sq_d = square(dv);

    Result results[3];

    snprintf(results[0].label, sizeof results[0].label, "int square");
    snprintf(results[0].value, sizeof results[0].value, "%d", sq_i);

    snprintf(results[1].label, sizeof results[1].label, "double square");
    snprintf(results[1].value, sizeof results[1].value, "%.2f", sq_d);

    snprintf(results[2].label, sizeof results[2].label, "print demo");
    snprintf(results[2].value, sizeof results[2].value, "see below");

    printf("=== _Generic results ===\n\n");
    for (int i = 0; i < 3; i++) {
        printf("  %s: %s\n", results[i].label, results[i].value);
    }

    printf("\n  print_val(iv)  → ");
    print_val(iv);
    printf("\n  print_val(dv)  → ");
    print_val(dv);
    printf("\n  print_val(sv)  → ");
    print_val(sv);
    printf("\n");

    return 0;
}
