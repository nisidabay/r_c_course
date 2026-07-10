/*
 * Exercise 01: Struct Definition
 *
 * Concept: struct keyword, member declaration, variable declaration.
 *
 * Fill in the blanks (marked /*@*//*@*/) to complete the program.
 * The program should define a struct Book, create two Book variables,
 * and print their details.
 *
 * Safe C Standard: use snprintf for string copy (NOT strcpy).
 */

#include <stdio.h>

/*@*/
/* Define a struct named 'Book' with:
 *   - char title[64]
 *   - char author[64]
 *   - int year
 */
/*@*/ {
    /*@*/
    char title[64];
    /*@*/
    /*@*/
} /*@*/ ;

int main(void) {
    /* Declare and initialise a Book variable */
    /*@*/ book1 = {"The C Programming Language", "Kernighan & Ritchie", 1978};

    /* Declare a second Book, then assign members */
    /*@*/ book2;
    snprintf(/*@*/.title, sizeof book2.title, "%s", "C: A Modern Approach");
    snprintf(book2.author, sizeof /*@*/, "%s", "K. N. King");
    book2.year = /*@*/;

    printf("Book 1: %s by %s (%d)\n", book1.title, book1.author, book1.year);
    printf("Book 2: %s by %s (%d)\n",
           /*@*/.title, book2.author, book2.year);

    return 0;
}
