/*
 * 05_structs_functions.c — passing structs by value vs by pointer
 *
 * By value:  the entire struct is COPIED — safe but expensive for large structs.
 * By pointer: only an address (8 bytes on x64) is passed — fast but mutable.
 *
 * This file shows the difference explicitly with a moderately-sized struct
 * so the performance / copy overhead is visible in principle.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[64];
    int  scores[20];     /* big-ish array to make copies noticeable */
    double average;
} Student;

/* Pass by value — whole struct is copied onto the stack */
double calc_average_by_value(Student s) {
    int sum = 0;
    for (int i = 0; i < 20; i++)
        sum += s.scores[i];
    s.average = sum / 20.0;   /* modifies the COPY only */
    return s.average;
}

/* Pass by pointer — only the address (8 bytes) is passed */
double calc_average_by_ptr(const Student *s) {
    int sum = 0;
    for (int i = 0; i < 20; i++)
        sum += s->scores[i];   /* no copy, read directly */
    return sum / 20.0;
}

int main(void) {
    Student stu;
    snprintf(stu.name, sizeof stu.name, "%s", "Diana");
    for (int i = 0; i < 20; i++)
        stu.scores[i] = 70 + i;   /* 70..89 */

    double avg1 = calc_average_by_value(stu);   /* copy */
    double avg2 = calc_average_by_ptr(&stu);    /* pointer */

    printf("By value:  average = %.1f  (original .average = %.1f, unchanged)\n",
           avg1, stu.average);
    printf("By ptr:    average = %.1f\n", avg2);

    return EXIT_SUCCESS;
}
/*
 * Thinking in C:
 *   — Pass-by-value copies EVERY member — O(n) time, stack pressure.
 *   — Pass-by-pointer passes 4-8 bytes regardless of struct size — O(1).
 *   — Use const T * when the function should NOT modify the original.
 *   — Passing by value lets you modify the copy safely; pointer lets you
 *     modify the original (or protect with const).
 */
