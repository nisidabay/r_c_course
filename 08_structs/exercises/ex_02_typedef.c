/*
 * Exercise 02: Typedef
 *
 * Concept: typedef struct { ... } TypeName;
 *
 * Fill in the blanks (marked /*@*//*@*/) to complete the program.
 * The program should use typedef to create a Movie type, then declare
 * and print Movie variables WITHOUT using the 'struct' keyword.
 *
 * Safe C Standard: use snprintf for string copy (NOT strcpy).
 */

#include <stdio.h>

/*@*/
/* Create a typedef for a struct with:
 *   - char title[64]
 *   - int year
 *   - double rating  (out of 10)
 * Name the alias 'Movie'.
 */
/*@*/ {
    char title[64];
    int  year;
    double rating;
} /*@*/ ;

/* Function that prints a Movie — takes Movie by value */
void print_movie(/*@*/ m) {
    printf("\"%s\" (%d) — %.1f/10\n", m.title, m.year, m.rating);
}

int main(void) {
    /* No 'struct' keyword needed — Movie is a type alias */
    /*@*/ m1 = {"The Matrix", 1999, 8.7};
    /*@*/ m2;
    snprintf(m2.title, sizeof m2.title, "%s", "Inception");
    m2.year   = 2010;
    m2.rating = /*@*/;

    print_movie(/*@*/);
    print_movie(m2);

    return 0;
}
