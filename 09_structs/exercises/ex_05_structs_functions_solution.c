/*
 * Exercise 05: Structs + Functions — SOLUTION
 *
 * Passing structs by value vs by pointer to functions.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

/* Pass by value — whole struct is copied */
Point add_points_by_value(Point a, Point b) {
    Point result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

/* Pass by pointer — only the address is passed */
void scale_by_ptr(Point *p, double factor) {
    p->x *= factor;
    p->y *= factor;
}

/* Print point — use const pointer to avoid copying but protect data */
void print_point(const Point *p) {
    printf("(%.1f, %.1f)\n", p->x, p->y);
}

int main(void) {
    /* Pass by value example */
    Point p1 = {3.0, 4.0};
    Point p2 = {1.0, 2.0};

    Point sum = add_points_by_value(p1, p2);

    printf("p1 = ");
    print_point(&p1);
    printf("p2 = ");
    print_point(&p2);
    printf("sum = ");
    print_point(&sum);

    /* Pass by pointer example — modifies original */
    printf("\nScaling p1 by 2.0...\n");
    scale_by_ptr(&p1, 2.0);
    printf("p1 after scale = ");
    print_point(&p1);

    return EXIT_SUCCESS;
}
