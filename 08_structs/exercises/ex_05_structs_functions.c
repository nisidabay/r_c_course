/*
 * Exercise 05: Structs + Functions
 *
 * Concept: Passing structs by value vs by pointer to functions.
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * The program defines a Point struct, then creates functions that
 * operate on Points by value and by pointer.
 *
 * Safe C Standard: use snprintf for string copy (NOT strcpy).
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

/* Pass by value — whole struct is copied */
Point add_points_by_value(Point a, Point b) {  // FIX ME  // FIX ME
    Point result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;  // FIX ME
    return result;
}

/* Pass by pointer — only the address is passed */
void scale_by_ptr(Point *p, double factor) {  // FIX ME
    p->x *= factor;
    p->y *= factor;  // FIX ME
}

/* Print point — use const pointer to avoid copying but protect data */
void print_point(const Point *p) {  // FIX ME
    printf("(%.1f, %.1f)\n", p->x, p->y);
}

int main(void) {
    /* Pass by value example */
    Point p1 = {3.0, 4.0};
    Point p2 = {1.0, 2.0};

    Point sum = add_points_by_value(p1, p2);  // FIX ME

    printf("p1 = ");
    print_point(&p1);
    printf("p2 = ");
    print_point(&p2);  // FIX ME
    printf("sum = ");
    print_point(&sum);

    /* Pass by pointer example — modifies original */
    printf("\nScaling p1 by 2.0...\n");
    scale_by_ptr(&p1, 2.0);  // FIX ME
    printf("p1 after scale = ");
    print_point(&p1);

    return EXIT_SUCCESS;
}
