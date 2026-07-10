/*
 * 06_struct_arrays.c — array of structs
 *
 * You can declare an array of any struct type. Each element is a full
 * struct. Initialise with brace-enclosed lists and iterate with a loop.
 *
 * Example: Person people[3]
 */

#include <stdio.h>

typedef struct {
    char   name[64];
    int    age;
    double height;
} Person;

int main(void) {
    /* Array initialisation — one brace pair per element */
    Person people[3] = {
        {"Alice",   30, 1.70},
        {"Bob",     25, 1.85},
        {"Charlie", 28, 1.78}
    };

    int n = sizeof people / sizeof people[0];

    printf("Friends list:\n");
    for (int i = 0; i < n; i++) {
        printf("  %d. %-8s  age %d  %.2f m\n",
               i + 1,
               people[i].name,
               people[i].age,
               people[i].height);
    }

    /* Modify one element through array indexing */
    snprintf(people[0].name, sizeof people[0].name, "%s", "Alicia");
    people[0].age = 31;
    people[0].height = 1.72;

    printf("\nAfter update:\n");
    for (int i = 0; i < n; i++) {
        printf("  %d. %-8s  age %d  %.2f m\n",
               i + 1,
               people[i].name,
               people[i].age,
               people[i].height);
    }

    return 0;
}
/*
 * Thinking in C:
 *   — people[i] is a full struct — use dot to access its members.
 *   — people[i].name is the char array inside element i.
 *   — sizeof array / sizeof element  gives the element count — a common
 *     C idiom (works only on the original array, not a decayed pointer).
 */
