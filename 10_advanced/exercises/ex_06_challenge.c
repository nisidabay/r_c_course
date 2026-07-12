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

typedef struct {
    char title[64];
    char author[64];
    int  year;
} Book;

int compare_by_title(const void *a, const void *b) {
    const Book *pa = (const Book *)a;
    const Book *pb = (const Book *)b;
    return strcmp(pa->title, pb->title);
}

int compare_by_author(const void *a, const void *b) {
    const Book *pa = (const Book *)a;
    const Book *pb = (const Book *)b;
    return strcmp(pa->author, pb->author);
}

int compare_by_year(const void *a, const void *b) {
    const Book *pa = (const Book *)a;
    const Book *pb = (const Book *)b;
    if (pa->year < pb->year) return -1;
    if (pa->year > pb->year) return 1;
    return 0;
}

/* ---- END OF YOUR CODE ---- */

int main(void) {
    /* ---- YOUR CODE HERE ---- */

    Book books[] = {
        {"1984", "George Orwell", 1949},
        {"Brave New World", "Aldous Huxley", 1932},
        {"The Catcher in the Rye", "J.D. Salinger", 1951},
        {"To Kill a Mockingbird", "Harper Lee", 1960},
        {"Fahrenheit 451", "Ray Bradbury", 1953},
    };
    size_t n = sizeof books / sizeof books[0];

    qsort(books, n, sizeof(Book), compare_by_title);
    printf("=== Sorted by title ===\n");
    for (size_t i = 0; i < n; i++) {
        printf("  \"%s\" by %s (%d)\n", books[i].title, books[i].author, books[i].year);
    }
    printf("\n");

    qsort(books, n, sizeof(Book), compare_by_author);
    printf("=== Sorted by author ===\n");
    for (size_t i = 0; i < n; i++) {
        printf("  \"%s\" by %s (%d)\n", books[i].title, books[i].author, books[i].year);
    }
    printf("\n");

    qsort(books, n, sizeof(Book), compare_by_year);
    printf("=== Sorted by year ===\n");
    for (size_t i = 0; i < n; i++) {
        printf("  \"%s\" by %s (%d)\n", books[i].title, books[i].author, books[i].year);
    }

    /* ---- END OF YOUR CODE ---- */

    return EXIT_SUCCESS;
}
