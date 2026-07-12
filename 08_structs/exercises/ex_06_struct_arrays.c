/*
 * Exercise 06: Struct Arrays
 *
 * Concept: Array of structs — declare, initialise, iterate, modify.
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * The program declares an array of Product structs, prints a catalogue,
 * updates a price, and prints again.
 *
 * Safe C Standard: use snprintf for string copy (NOT strcpy).
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char   name[64];
    double price;
    int    quantity;
} Product;

int main(void) {
    /* Array initialisation — one brace pair per element */
    Product catalogue[4] = {
        {"Laptop",    999.99, 10},
        {"Mouse",      29.99, 50},
        {"Keyboard",   89.99, 30},
        {"Monitor",   349.99, 15}
    };

    int n = sizeof catalogue / sizeof catalogue[0];  // FIX ME

    printf("Product Catalogue:\n");
    for (int i = 0; i < n; i++) {
        printf("  %d. %-10s $%7.2f  (qty: %d)\n",
               i + 1,
               catalogue[i].name,  // FIX ME
               catalogue[i].price,
               catalogue[i].quantity);  // FIX ME
    }

    /* Update the price of the first product (Laptop) */
    catalogue[0].price = 899.99;  // FIX ME

    /* Update the quantity of the third product (Keyboard) — use dot */
    catalogue[2].quantity = 45;  // FIX ME

    printf("\nAfter updates:\n");
    for (int i = 0; i < n; i++) {
        printf("  %d. %-10s $%7.2f  (qty: %d)\n",
               i + 1,
               catalogue[i].name,
               catalogue[i].price,
               catalogue[i].quantity);
    }

    return EXIT_SUCCESS;
}
