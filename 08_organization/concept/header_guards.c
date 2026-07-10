/*
 * How do I prevent multiple inclusion with header guards?
 *
 * Header guards use the preprocessor pattern #ifndef / #define / #endif
 * to ensure a header is only processed once per translation unit,
 * preventing duplicate type definitions and redeclaration errors.
 *
 * This file demonstrates the pattern by defining a type inline
 * (as if it were in a header) and using it in the same file.
 */

#include <stdio.h>
#include <stdlib.h>

/* ---- header guard pattern ---- */
/* In a real .h file this would be:
 *   #ifndef VECTOR3_H
 *   #define VECTOR3_H
 *   ... declarations ...
 *   #endif   // VECTOR3_H
 */

#ifndef VECTOR3_H
#define VECTOR3_H

typedef struct {
    double x;
    double y;
    double z;
} Vector3;

static const Vector3 VEC3_ZERO = {0.0, 0.0, 0.0};

#endif /* VECTOR3_H */

/* ---- usage ---- */

static double vec3_length(const Vector3 *v)
{
    if (v == NULL) return 0.0;
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

int main(void)
{
    Vector3 pos = {1.0, 2.0, 3.0};

    printf("Position: (%.1f, %.1f, %.1f)\n", pos.x, pos.y, pos.z);
    printf("Length^2: %.2f\n", vec3_length(&pos));
    printf("Zero:     (%.1f, %.1f, %.1f)\n",
           VEC3_ZERO.x, VEC3_ZERO.y, VEC3_ZERO.z);

    return EXIT_SUCCESS;
}

/* Thinking in C: Always guard headers with #ifndef / #define / #endif
 * (or #pragma once for compiler-specific code). This prevents the
 * cascading errors that occur when a type or function gets declared twice. */


// 💡 Thinking in C:
// Header guards (hash-ifndef / hash-define / hash-endif) prevent double inclusion. Always use them.
