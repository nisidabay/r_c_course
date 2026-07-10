#include <stdio.h>

int main(void) {
    int limit = 20;

    puts("Break: stop searching at first multiple of 7\n");

    for (int i = 1; i <= limit; i++) {
        if (i % 7 == 0) {
            printf("Found! %d is a multiple of 7.\n", i);
            break;
        }
        printf("  %d is not a multiple of 7.\n", i);
    }

    puts("\nContinue: print only odd numbers from 1 to 10\n");

    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;
        }
        printf("%d is odd.\n", i);
    }

    puts("\nEarly exit on threshold:\n");

    int readings[] = {12, 18, 15, 34, 22, 9, 27};
    int num_readings = 7;

    for (int i = 0; i < num_readings; i++) {
        if (readings[i] > 30) {
            printf("Alert! Reading %d exceeded threshold.\n", readings[i]);
            break;
        }
        printf("Reading %d: OK\n", readings[i]);
    }

    return 0;
}

// Thinking in C:
// break exits the innermost loop immediately, transferring
// control to the statement after the loop. continue skips
// the rest of the current iteration and jumps to the
// increment/condition check. Both work inside for, while,
// and do-while loops in C.
