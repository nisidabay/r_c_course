/*
 * How do I split code across multiple files?
 *
 * Multi-file projects use .h files for declarations and .c files for
 * definitions. Each .c is compiled separately, then linked together.
 *
 * Typical structure:
 *   math_utils.h   -- forward declarations
 *   math_utils.c   -- implementations
 *   main.c         -- uses math_utils
 *
 * Build:
 *   gcc -std=c11 -Wall -Wextra -pedantic -Werror -c math_utils.c
 *   gcc -std=c11 -Wall -Wextra -pedantic -Werror -c main.c
 *   gcc -o program math_utils.o main.o
 *
 * This file demonstrates the pattern with forward declarations
 * and implementations side by side, as a single self-contained unit.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ---- forward declarations (would be in math_utils.h) ---- */

static double circle_area(double radius);
static double celsius_to_fahrenheit(double c);
static void   print_stats(const double *values, size_t count);

/* ---- implementations (would be in math_utils.c) ---- */

static double circle_area(double radius)
{
    if (radius < 0.0) return 0.0;
    return M_PI * radius * radius;
}

static double celsius_to_fahrenheit(double c)
{
    return c * 9.0 / 5.0 + 32.0;
}

static void print_stats(const double *values, size_t count)
{
    if (values == NULL || count == 0) return;

    double sum = 0.0;
    double max = values[0];
    double min = values[0];

    for (size_t i = 0; i < count; i++)
    {
        double v = values[i];
        sum += v;
        if (v > max) max = v;
        if (v < min) min = v;
    }

    double avg = sum / (double)count;
    printf("count=%zu  sum=%.2f  avg=%.2f  min=%.2f  max=%.2f\n",
           count, sum, avg, min, max);
}

/* ---- entry point (would be main.c) ---- */

int main(void)
{
    double radius = 5.0;
    printf("circle_area(%.1f) = %.2f\n", radius, circle_area(radius));

    double temp_c = 100.0;
    printf("%.1f C = %.1f F\n", temp_c, celsius_to_fahrenheit(temp_c));

    double data[] = {3.1, 4.5, 2.8, 9.2, 1.7};
    print_stats(data, sizeof(data) / sizeof(data[0]));

    return EXIT_SUCCESS;
}

/* Thinking in C: Split code across .h (declarations) and .c (definitions)
 * for modularity. Compile each .c to an object file, then link them.
 * Forward declarations let the compiler check types across files. */


// 💡 Thinking in C:
// Split code into multiple .c files for organization. Share declarations via header files with guards.
