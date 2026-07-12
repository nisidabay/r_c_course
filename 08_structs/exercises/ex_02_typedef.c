/*
 * Exercise 02: Typedef
 *
 * Concept: typedef struct { ... } TypeName;
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * The program should use typedef to create a Movie type, then declare
 * and print Movie variables WITHOUT using the 'struct' keyword.
 *
 * Safe C Standard: use snprintf for string copy (NOT strcpy).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FIX ME
/* Create a typedef for a struct with:
 *   - char title[64]
 *   - int year
 *   - double rating  (out of 10)
 * Name the alias 'Movie'.
 */
typedef struct {  // FIX ME
    char title[64];
    int  year;
    double rating;
} Movie;  // FIX ME

/* Function that prints a Movie — takes Movie by value */
void print_movie(Movie m) {  // FIX ME
    printf("\"%s\" (%d) — %.1f/10\n", m.title, m.year, m.rating);
}

int main(void) {
    /* No 'struct' keyword needed — Movie is a type alias */
    Movie m1 = {"The Matrix", 1999, 8.7};  // FIX ME
    Movie m2;  // FIX ME
    snprintf(m2.title, sizeof m2.title, "%s", "Inception");
    m2.year   = 2010;
    m2.rating = 8.8;  // FIX ME

    print_movie(m1);  // FIX ME
    print_movie(m2);

    return EXIT_SUCCESS;
}
