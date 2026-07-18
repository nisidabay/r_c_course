/*
 * Exercise 07 — Union: Shape Area Calculator — SOLUTION
 */

#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159f

enum shape_type { SHAPE_CIRCLE, SHAPE_RECTANGLE };

struct rectangle {
    float width;
    float height;
};

union shape_data {
    float radius;
    struct rectangle rect;
};

struct tagged_shape {
    enum shape_type tag;
    union shape_data data;
};

static float area(struct tagged_shape *s)
{
    switch (s->tag) {
    case SHAPE_CIRCLE:
        return PI * s->data.radius * s->data.radius;
    case SHAPE_RECTANGLE:
        return s->data.rect.width * s->data.rect.height;
    }
    return 0.0f;
}

int main(void)
{
    struct tagged_shape circle = { SHAPE_CIRCLE, .data.radius = 5.0f };
    struct tagged_shape rect   = { SHAPE_RECTANGLE, .data.rect = { 3.0f, 4.0f } };

    printf("Circle(r=5.0):   area = %.2f\n", area(&circle));
    printf("Rectangle(3x4):  area = %.2f\n", area(&rect));

    return EXIT_SUCCESS;
}
