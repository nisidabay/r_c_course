/*
 * Exercise 01: Struct Definition
 *
 * Concept: A struct is a user-defined type that groups related data.
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FIX ME — define struct Book with title[100], author[100], year
struct Book {
    char title[100];
    char author[100];
    int year;
};

int main(void) {
    // FIX ME — declare and initialize book1
    struct Book book1 = {"The C Programming Language", "Kernighan & Ritchie", 1978};

    // FIX ME — declare book2, then set fields
    struct Book book2;
    snprintf(book2.title, sizeof book2.title, "%s", "C: A Modern Approach");
    snprintf(book2.author, sizeof book2.author, "%s", "K. N. King");
    book2.year = 2008;

    printf("Book: %s by %s (%d)\n",
           book1.title, book1.author, book1.year);
    printf("Book: %s by %s (%d)\n",
           book2.title, book2.author, book2.year);

    return EXIT_SUCCESS;
}
