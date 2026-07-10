/*
 * How do I dynamically allocate structs?
 *
 * This file demonstrates malloc(sizeof(MyStruct)) and accessing
 * struct members through a pointer with the -> operator.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Point {
    double x;
    double y;
};

struct Person {
    char name[64];
    int age;
};

int main(void) {
    /* Allocate a single struct on the heap */
    struct Point *p = (struct Point *)malloc(sizeof(struct Point));
    if (p == NULL) {
        perror("malloc failed for Point");
        return EXIT_FAILURE;
    }

    p->x = 3.5;
    p->y = -1.2;

    printf("Point: (%.1f, %.1f)\n", p->x, p->y);

    free(p);
    p = NULL;

    /* Allocate an array of structs on the heap */
    struct Person *people = (struct Person *)malloc(3 * sizeof(struct Person));
    if (people == NULL) {
        perror("malloc failed for Person array");
        return EXIT_FAILURE;
    }

    snprintf(people[0].name, sizeof(people[0].name), "Alice");
    people[0].age = 30;
    snprintf(people[1].name, sizeof(people[1].name), "Bob");
    people[1].age = 25;
    snprintf(people[2].name, sizeof(people[2].name), "Charlie");
    people[2].age = 35;

    for (size_t i = 0; i < 3; i++) {
        printf("Person %zu: %s, %d\n", i, people[i].name, people[i].age);
    }

    free(people);
    people = NULL;

    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// malloc can allocate structs too: (Person *)malloc(sizeof(Person)). Works for any type.
