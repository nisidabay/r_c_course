/*
 * Exercise 01: Struct Definition — SOLUTION
 *
 * struct keyword, member declaration, variable declaration.
 */

#include <stdio.h>

/* Solution: define a struct named 'Book' */
struct Book {
    char title[64];
    char author[64];
    int  year;
};

int main(void) {
    /* Declare and initialise a Book variable */
    struct Book book1 = {"The C Programming Language", "Kernighan & Ritchie", 1978};

    /* Declare a second Book, then assign members */
    struct Book book2;
    snprintf(book2.title, sizeof book2.title, "%s", "C: A Modern Approach");
    snprintf(book2.author, sizeof book2.author, "%s", "K. N. King");
    book2.year = 2008;

    printf("Book 1: %s by %s (%d)\n", book1.title, book1.author, book1.year);
    printf("Book 2: %s by %s (%d)\n",
           book2.title, book2.author, book2.year);

    return 0;
}
