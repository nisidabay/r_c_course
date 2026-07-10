/*
 * ex_06_challenge_solution.c
 * Group 10 — Advanced
 * Challenge: function pointers + qsort + struct — SOLUTION
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- struct definition ---------- */
typedef struct {
    char title[64];
    char author[64];
    int  year;
} Book;

/* ---------- comparator: by title ---------- */
static int compare_by_title(const void *a, const void *b) {
    const Book *pa = (const Book *)a;
    const Book *pb = (const Book *)b;
    return strcmp(pa->title, pb->title);
}

/* ---------- comparator: by author ---------- */
static int compare_by_author(const void *a, const void *b) {
    const Book *pa = (const Book *)a;
    const Book *pb = (const Book *)b;
    return strcmp(pa->author, pb->author);
}

/* ---------- comparator: by year ---------- */
static int compare_by_year(const void *a, const void *b) {
    const Book *pa = (const Book *)a;
    const Book *pb = (const Book *)b;
    if (pa->year > pb->year) return +1;
    if (pa->year < pb->year) return -1;
    return 0;
}

/* ---------- helper: print a book ---------- */
static void print_book(const Book *b) {
    printf("  \"%s\" by %s (%d)\n", b->title, b->author, b->year);
}

/* ---------- helper: print an array of books ---------- */
static void print_books(const Book *books, size_t n, const char *label) {
    printf("\n=== %s ===\n", label);
    for (size_t i = 0; i < n; i++) {
        print_book(&books[i]);
    }
}

int main(void) {
    Book books[] = {
        { .title = "Brave New World",  .author = "Aldous Huxley",   .year = 1932 },
        { .title = "1984",             .author = "George Orwell",   .year = 1949 },
        { .title = "Fahrenheit 451",   .author = "Ray Bradbury",    .year = 1953 },
        { .title = "Dune",             .author = "Frank Herbert",   .year = 1965 },
        { .title = "Neuromancer",      .author = "William Gibson",  .year = 1984 },
        { .title = "Snow Crash",       .author = "Neal Stephenson", .year = 1992 },
    };
    size_t n = sizeof books / sizeof books[0];

    /* sort by title */
    qsort(books, n, sizeof(Book), compare_by_title);
    print_books(books, n, "Sorted by title");

    /* sort by author */
    qsort(books, n, sizeof(Book), compare_by_author);
    print_books(books, n, "Sorted by author");

    /* sort by year */
    qsort(books, n, sizeof(Book), compare_by_year);
    print_books(books, n, "Sorted by year");

    return 0;
}
