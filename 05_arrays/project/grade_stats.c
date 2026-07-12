/*
 * grade_stats.c — Grade Statistics Tool
 *
 * Reads up to 20 student scores (0–100) from stdin, computes
 * min/max/average/passing-count, sorts scores via selection sort,
 * and displays the results.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic grade_stats.c -o grade_stats
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stddef.h>   /* size_t */
#include <stdlib.h>   /* EXIT_FAILURE */
#include <string.h>

#define MAX_SCORES 20

/*
 * read_scores — read integer scores from stdin using fgets + strtol.
 * Returns the number of scores successfully read.
 */
static size_t read_scores(int scores[], size_t capacity)
{
    char line[64];
    size_t count = 0;

    while (count < capacity && fgets(line, sizeof line, stdin) != NULL) {
        int val;
        line[strcspn(line, "\n")] = '\0';

        char *endptr;
        errno = 0;
        long v = strtol(line, &endptr, 10);
        if (errno == ERANGE || endptr == line || *endptr != '\0') {
            continue;               /* skip blank / non-numeric lines */
        }
        if (v < INT_MIN || v > INT_MAX) {
            continue;
        }
        val = (int)v;
        if (val < 0 || val > 100) {
            continue;               /* skip out-of-range scores */
        }
        scores[count] = val;
        ++count;
    }

    return count;
}

/*
 * swap — exchange two integers.
 */
static void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/*
 * sort_scores — selection sort (ascending).
 */
static void sort_scores(int scores[], size_t n)
{
    for (size_t i = 0; i < n - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (scores[j] < scores[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(&scores[i], &scores[min_idx]);
        }
    }
}

/*
 * compute_min — return the smallest value in the array.
 */
static int compute_min(const int scores[], size_t n)
{
    int m = scores[0];
    for (size_t i = 1; i < n; ++i) {
        if (scores[i] < m) {
            m = scores[i];
        }
    }
    return m;
}

/*
 * compute_max — return the largest value in the array.
 */
static int compute_max(const int scores[], size_t n)
{
    int m = scores[0];
    for (size_t i = 1; i < n; ++i) {
        if (scores[i] > m) {
            m = scores[i];
        }
    }
    return m;
}

/*
 * compute_average — return the arithmetic mean as a double.
 */
static double compute_average(const int scores[], size_t n)
{
    int sum = 0;
    for (size_t i = 0; i < n; ++i) {
        sum += scores[i];
    }
    return (double)sum / (double)n;
}

/*
 * count_passing — number of scores >= 60.
 */
static size_t count_passing(const int scores[], size_t n)
{
    size_t cnt = 0;
    for (size_t i = 0; i < n; ++i) {
        if (scores[i] >= 60) {
            ++cnt;
        }
    }
    return cnt;
}

int main(void)
{
    int scores[MAX_SCORES];

    /* sizeof trick: derive array capacity from the array's own size */
    size_t capacity = sizeof scores / sizeof scores[0];

    printf("Enter up to %zu student scores (0–100), one per line.\n"
           "Press Ctrl-D (EOF) when done.\n\n",
           capacity);

    size_t count = read_scores(scores, capacity);

    if (count == 0) {
        printf("No valid scores entered. Exiting.\n");
        return EXIT_FAILURE;
    }

    /* --- statistics --- */
    int    min  = compute_min(scores, count);
    int    max  = compute_max(scores, count);
    double avg  = compute_average(scores, count);
    size_t pass = count_passing(scores, count);

    /* --- sort --- */
    sort_scores(scores, count);

    /* --- display --- */
    printf("\n--- Sorted Scores ---\n");
    for (size_t i = 0; i < count; ++i) {
        printf("  %2zu: %3d\n", i + 1, scores[i]);
    }

    printf("\n--- Statistics ---\n");
    printf("  Count  : %zu\n", count);
    printf("  Min    : %d\n", min);
    printf("  Max    : %d\n", max);
    printf("  Average: %.1f\n", avg);
    printf("  Passing (>=60): %zu / %zu\n", pass, count);

    return EXIT_SUCCESS;
}
