/*
 * Exercise 03: Member Access (.)
 *
 * Concept: The dot (.) operator for direct access to struct members,
 * including nested structs.
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * The program defines a nested struct (Address inside Employee) and
 * prints employee details using chained dot access.
 *
 * Safe C Standard: use snprintf for string copy (NOT strcpy).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char street[64];
    char city[32];
    int  zip;
} Address;

typedef struct {
    char    name[64];
    int     id;
    Address addr;    /* nested struct */
} Employee;

int main(void) {
    Employee e;

    snprintf(e.name, sizeof e.name, "%s", "Jane Smith");
    e.id = 1001;

    /* Fill in the chained dot access to set nested members */
    snprintf(e.addr.street, sizeof e.addr.street, "%s", "456 Pine Rd");  // FIX ME
    snprintf(e.addr.city, sizeof e.addr.city, "%s", "Seattle");  // FIX ME
    e.addr.zip = 98101;  // FIX ME  // FIX ME

    printf("Employee: %s (ID: %d)\n", e.name, e.id);
    printf("Address:  %s\n", e.addr.street);  // FIX ME
    printf("City:     %s\n", e.addr.city);  // FIX ME  // FIX ME
    printf("ZIP:      %d\n", e.addr.zip);

    return EXIT_SUCCESS;
}
