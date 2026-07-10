/*
 * 03_member_access.c — . operator for direct access, nested structs
 *
 * Use the dot (.) operator to read or write a member of a struct variable.
 * Structs can contain other structs as members (nesting).
 *
 * Example: Address nested inside Person
 */

#include <stdio.h>

typedef struct {
    char street[64];
    char city[32];
    int  zip;
} Address;

typedef struct {
    char    name[64];
    int     age;
    Address addr;       /* nested struct */
} Person;

int main(void) {
    Person p;

    snprintf(p.name, sizeof p.name, "%s", "Charlie");
    p.age = 28;

    /* Access nested members with chained dots */
    snprintf(p.addr.street, sizeof p.addr.street, "%s", "123 Oak St");
    snprintf(p.addr.city,   sizeof p.addr.city,   "%s", "Portland");
    p.addr.zip = 97201;

    printf("Name:  %s (%d)\n", p.name, p.age);
    printf("Lives: %s, %s  %d\n",
           p.addr.street, p.addr.city, p.addr.zip);

    return 0;
}
/*
 * Thinking in C:
 *   — The . operator binds left-to-right: p.addr.street means
 *     (p.addr).street.
 *   — Nested structs are stored inline — Address fields sit inside Person's
 *     memory block.
 *   — No pointer needed; dot works directly on the struct variable.
 */
