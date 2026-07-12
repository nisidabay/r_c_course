/*
 * Exercise 04: Arrow Operator (->)
 *
 * Concept: ptr->member as syntactic sugar for (*ptr).member.
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * The program shows both arrow and deref+dot forms for accessing
 * struct members through a pointer.
 *
 * Safe C Standard: use snprintf for string copy (NOT strcpy).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char model[64];
    int  year;
    double price;
} Car;

int main(void) {
    Car tesla = {"Model 3", 2024, 44990.0};
    Car *ptr = &tesla;    /* pointer to the struct */  // FIX ME

    /* Arrow form — preferred */
    printf("Arrow:     %s (%d) — $%.2f\n",
           ptr->model, ptr->year, ptr->price);  // FIX ME

    /* Dereference-then-dot form — equivalent */
    printf("Deref+dot: %s (%d) — $%.2f\n",
           (*ptr).model, (*ptr).year, (*ptr).price);  // FIX ME  // FIX ME

    /* Modify year through pointer using arrow */
    ptr->year = 2025;  // FIX ME
    printf("Updated year (arrow): %d\n", ptr->year);

    /* Modify year through pointer using deref+dot */
    (*ptr).year = 2026;
    printf("Updated year ((*ptr)): %d\n", ptr->year);

    /* Modify model through pointer */
    snprintf(ptr->model, sizeof ptr->model, "%s", "Model Y");  // FIX ME
    printf("Updated model: %s\n", (*ptr).model);  // FIX ME

    return EXIT_SUCCESS;
}
