/*
 * ex_06_challenge.c
 * Group 10 — Advanced
 * Challenge: function pointers + qsort + struct
 *
 * CHALLENGE: Sort an array of structs by different fields using
 * different comparator functions, all passed as function pointers.
 *
 * TASKS:
 *   1. Define typedef struct Book with fields:
 *        char title[64]
 *        char author[64]
 *        int  year
 *   2. Write 3 comparator functions (all compatible with qsort's
 *      int (*)(const void *, const void *) signature):
 *        - compare_by_title: alphabetical by title
 *        - compare_by_author: alphabetical by author
 *        - compare_by_year: ascending by year
 *   3. In main(), declare an array of at least 5 Book structs
 *   4. Use qsort with each comparator and print results clearly
 *
 * RULES:
 *   - No strcpy/strcat/sprintf/scanf/atoi/atof
 *   - Use snprintf for building strings
 *   - int main(void)
 *   - Compiles with -std=c11 -Wall -Wextra -pedantic
 *
 * EXAMPLE expected output (book order may vary with your data):
 *
 *   === Sorted by title ===
 *   "1984" by George Orwell (1949)
 *   "Brave New World" by Aldous Huxley (1932)
 *   ...
 *
 *   === Sorted by author ===
 *   ...
 *
 *   === Sorted by year ===
 *   ...
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- YOUR CODE HERE ---- */
















/* ---- END OF YOUR CODE ---- */

int main(void) {
    /* ---- YOUR CODE HERE ---- */
















    /* ---- END OF YOUR CODE ---- */

    return 0;
}
