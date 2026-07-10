/*
 * 02_typedef.c — typedef struct { ... } Person;
 *
 * typedef creates an alias so you don't have to write 'struct' every time.
 * Most modern C code uses typedef for struct types.
 */

#include <stdio.h>

typedef struct {
    char   name[64];
    int    age;
    double height;
} Person;

void print_person(Person p) {
    printf("%s is %d years old, %.2f m tall\n", p.name, p.age, p.height);
}

int main(void) {
    /* No 'struct' keyword needed — Person is the type name */
    Person alice = {"Alice", 30, 1.70};
    Person bob   = {"Bob",   25, 1.85};

    print_person(alice);
    print_person(bob);

    return 0;
}
/*
 * Thinking in C:
 *   — typedef is a storage-class specifier; it does NOT create a new type,
 *     only an alias for an existing (anonymous) struct.
 *   — Without typedef you'd write 'struct Person' everywhere — tedious.
 *   — The alias is interchangeable with the full struct type.
 */
