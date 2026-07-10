/*
 * 01_struct_def.c — struct keyword, member declaration, variable declaration
 *
 * A struct is a user-defined type that groups related variables (members)
 * under one name. Members can be of any type.
 *
 * Example: Person { name, age, height }
 */

#include <stdio.h>
#include <string.h>

struct Person {
    char  name[64];
    int   age;
    double height;   /* metres */
};

int main(void) {
    /* Declare and initialise a struct variable */
    struct Person alice = {"Alice", 30, 1.70};

    /* Declare, then assign member-by-member */
    struct Person bob;
    snprintf(bob.name, sizeof bob.name, "%s", "Bob");
    bob.age    = 25;
    bob.height = 1.85;

    printf("Name:   %s\n", alice.name);
    printf("Age:    %d\n", alice.age);
    printf("Height: %.2f m\n\n", alice.height);

    printf("Name:   %s\n", bob.name);
    printf("Age:    %d\n", bob.age);
    printf("Height: %.2f m\n", bob.height);

    return 0;
}
/*
 * Thinking in C:
 *   — struct creates a blueprint; variables of that type hold real data.
 *   — Members occupy contiguous memory (subject to alignment/padding).
 *   — Use snprintf instead of strcpy for strings — it's safe.
 */
