/*
 * Exercise 02: Typedef — SOLUTION
 *
 * typedef struct { ... } TypeName;
 */

#include <stdio.h>

/* Solution: typedef with Movie alias */
typedef struct {
    char title[64];
    int  year;
    double rating;
} Movie;

/* Function that prints a Movie — takes Movie by value */
void print_movie(Movie m) {
    printf("\"%s\" (%d) — %.1f/10\n", m.title, m.year, m.rating);
}

int main(void) {
    /* No 'struct' keyword needed — Movie is a type alias */
    Movie m1 = {"The Matrix", 1999, 8.7};
    Movie m2;
    snprintf(m2.title, sizeof m2.title, "%s", "Inception");
    m2.year   = 2010;
    m2.rating = 8.8;

    print_movie(m1);
    print_movie(m2);

    return 0;
}
