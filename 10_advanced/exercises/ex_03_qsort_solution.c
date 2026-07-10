/*
 * ex_03_qsort_solution.c
 * Group 10 — Advanced
 * Exercise 03: qsort with callbacks — SOLUTION
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char  name[32];
    int   age;
} Person;

int compare_by_age(const void *a, const void *b) {
    const Person *pa = (const Person *)a;
    const Person *pb = (const Person *)b;

    if (pa->age > pb->age) return +1;
    if (pa->age < pb->age) return -1;
    return 0;
}

int compare_by_name(const void *a, const void *b) {
    const Person *pa = (const Person *)a;
    const Person *pb = (const Person *)b;
    return strcmp(pa->name, pb->name);
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

    qsort(people, n, sizeof(Person), compare_by_age);

    printf("Sorted by age:\n");
    for (size_t i = 0; i < n; i++) {
        printf("  %s (%d)\n", people[i].name, people[i].age);
    }

    qsort(people, n, sizeof(Person), compare_by_name);

    printf("\nSorted by name:\n");
    for (size_t i = 0; i < n; i++) {
        printf("  %s (%d)\n", people[i].name, people[i].age);
    }

    return 0;
}
