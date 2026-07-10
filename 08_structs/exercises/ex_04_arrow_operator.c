/*
 * Exercise 04: Arrow Operator (->)
 *
 * Concept: ptr->member as syntactic sugar for (*ptr).member.
 *
 * Fill in the blanks (marked /*@*//*@*/) to complete the program.
 * The program shows both arrow and deref+dot forms for accessing
 * struct members through a pointer.
 *
 * Safe C Standard: use snprintf for string copy (NOT strcpy).
 */

#include <stdio.h>

typedef struct {
    char model[64];
    int  year;
    double price;
} Car;

int main(void) {
    Car tesla = {"Model 3", 2024, 44990.0};
    Car *ptr = /*@*/;    /* pointer to the struct */

    /* Arrow form — preferred */
    printf("Arrow:     %s (%d) — $%.2f\n",
           ptr->/*@*/, ptr->year, ptr->price);

    /* Dereference-then-dot form — equivalent */
    printf("Deref+dot: %s (%d) — $%.2f\n",
           (*ptr)/*@*/model, (*ptr)./*@*/, (*ptr).price);

    /* Modify year through pointer using arrow */
    /*@*/->year = 2025;
    printf("Updated year (arrow): %d\n", ptr->year);

    /* Modify year through pointer using deref+dot */
    (*ptr).year = 2026;
    printf("Updated year ((*ptr)): %d\n", ptr->year);

    /* Modify model through pointer */
    snprintf(ptr->/*@*/, sizeof ptr->model, "%s", "Model Y");
    printf("Updated model: %s\n", (*ptr)./*@*/);

    return 0;
}
