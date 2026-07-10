/*
 * Exercise 06: Struct Arrays
 *
 * Concept: Array of structs — declare, initialise, iterate, modify.
 *
 * Fill in the blanks (marked /*@*//*@*/) to complete the program.
 * The program declares an array of Product structs, prints a catalogue,
 * updates a price, and prints again.
 *
 * Safe C Standard: use snprintf for string copy (NOT strcpy).
 */

#include <stdio.h>

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

    int n = sizeof catalogue /*@*/ sizeof catalogue[0];

    printf("Product Catalogue:\n");
    for (int i = 0; i < n; i++) {
        printf("  %d. %-10s $%7.2f  (qty: %d)\n",
               i + 1,
               catalogue[/*@*/].name,
               catalogue[i].price,
               catalogue[i]./*@*/);
    }

    /* Update the price of the first product (Laptop) */
    catalogue[/*@*/].price = 899.99;

    /* Update the quantity of the third product (Keyboard) — arrow style?
     * No — catalogue[2] is a struct, not a pointer. Use dot. */
    catalogue[2]./*@*/ = 45;

    printf("\nAfter updates:\n");
    for (int i = 0; i < n; i++) {
        printf("  %d. %-10s $%7.2f  (qty: %d)\n",
               i + 1,
               catalogue[i].name,
               catalogue[i].price,
               catalogue[i].quantity);
    }

    return 0;
}
