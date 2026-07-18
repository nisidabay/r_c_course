#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int count = 1;
    int limit = 5;

    puts("Countdown to Liftoff\n");

    while (count <= limit) {
        printf("T-minus %d...\n", limit - count + 1);
        count++;
    }
    puts("Liftoff!\n");

    double balance = 100.0;
    double rate = 0.05;
    int years = 0;

    puts("Growth of $100.00 at 5%% interest:");
    while (balance < 200.0) {
        balance = balance + balance * rate;
        years++;
        printf("Year %d: $%.2f\n", years, balance);
    }

    return EXIT_SUCCESS;
}

// Thinking in C:
// A while loop checks the condition BEFORE each iteration.
// If the condition is false initially, the body never runs.
// C interprets any non-zero value as true in a condition;
// zero means false. The loop variable must be updated
// manually inside the body to avoid infinite loops.
