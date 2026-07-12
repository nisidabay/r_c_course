#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int total = 0;
    int count = 10;

    puts("Summing 1 through 10:\n");

    for (int i = 1; i <= count; i++) {
        total = total + i;
        printf("Step %d: running total = %d\n", i, total);
    }
    printf("\nFinal sum: %d\n\n", total);

    int steps = 5;
    puts("Multiplication table for 7:");
    for (int row = 1; row <= steps; row++) {
        printf("7 x %d = %d\n", row, 7 * row);
    }

    return EXIT_SUCCESS;
}

// Thinking in C:
// The for loop bundles init, condition, and increment into
// a single line, reducing scope for off-by-one errors.
// The counter variable declared inside the for header is
// scoped to the loop (C99 and later). All three clauses
// are optional — for (;;) is an infinite loop in C.
