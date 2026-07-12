/*
 * ex_03_qsort.c
 * Group 10 — Advanced
 * Exercise 03: qsort with callbacks
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * Read the comments to understand what each line should do.
 *
 * NOTE: The comparator signature for qsort is:
 *   int cmp(const void *a, const void *b);
 * You must cast the void* pointers before dereferencing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char  name[32];
    int   age;
} Person;

/* ---------- comparator: sort by age ascending ---------- */
int compare_by_age(const void *a, const void *b) {
    /* cast void* → const Person* */
    const Person *pa = (const Person *)a;  // FIX ME
    const Person *pb = (const Person *)b;  // FIX ME

    /* compare ages */
    if (pa->age > pb->age) return +1;
    if (pa->age < pb->age) return -1;  // FIX ME
    return 0;
}

/* ---------- comparator: sort by name alphabetically ---------- */
int compare_by_name(const void *a, const void *b) {  // FIX ME
    const Person *pa = (const Person *)a;
    const Person *pb = (const Person *)b;
    return strcmp(pa->name, pb->name);  // FIX ME
}

int main(void) {
    Person people[] = {
        { .name = "Zara",  .age = 28 },
        { .name = "Alex",  .age = 35 },
        { .name = "Maya",  .age = 22 },
        { .name = "Ben",   .age = 35 },
        { .name = "Leila", .age = 31 },
    };
    size_t n = sizeof people / sizeof people[0];

    /* --- sort by age --- */
    qsort(people, n, sizeof(Person), compare_by_age);  // FIX ME

    printf("Sorted by age:\n");
    for (size_t i = 0; i < n; i++) {
        printf("  %s (%d)\n", people[i].name, people[i].age);
    }

    /* --- sort by name --- */
    qsort(people, n, sizeof(Person), compare_by_name);  // FIX ME

    printf("\nSorted by name:\n");
    for (size_t i = 0; i < n; i++) {
        printf("  %s (%d)\n", people[i].name, people[i].age);
    }

    return EXIT_SUCCESS;
}
