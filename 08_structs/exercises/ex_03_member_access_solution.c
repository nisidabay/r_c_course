/*
 * Exercise 03: Member Access — SOLUTION
 *
 * Dot (.) operator for direct access, including nested structs.
 */

#include <stdio.h>

typedef struct {
    char street[64];
    char city[32];
    int  zip;
} Address;

typedef struct {
    char    name[64];
    int     id;
    Address addr;
} Employee;

int main(void) {
    Employee e;

    snprintf(e.name, sizeof e.name, "%s", "Jane Smith");
    e.id = 1001;

    /* Chained dot access to set nested members */
    snprintf(e.addr.street, sizeof e.addr.street, "%s", "456 Pine Rd");
    snprintf(e.addr.city, sizeof e.addr.city, "%s", "Seattle");
    e.addr.zip = 98101;

    printf("Employee: %s (ID: %d)\n", e.name, e.id);
    printf("Address:  %s\n", e.addr.street);
    printf("City:     %s\n", e.addr.city);
    printf("ZIP:      %d\n", e.addr.zip);

    return 0;
}
