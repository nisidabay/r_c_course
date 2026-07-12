#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int score = 82;

    puts("Grade Checker\n");

    if (score >= 90) {
        puts("Grade: A — Excellent work!");
    } else if (score >= 75) {
        puts("Grade: B — Good job, keep it up!");
    } else if (score >= 60) {
        puts("Grade: C — Passing, room to improve.");
    } else {
        puts("Grade: F — Needs more practice.");
    }

    score = 45;
    printf("With a score of %d:\n", score);
    if (score >= 60) {
        puts("Result: Passed.");
    } else {
        puts("Result: Failed.");
    }

    int temperature = 30;
    printf("\nTemperature: %d C\n", temperature);
    if (temperature > 35) {
        puts("Advisory: Heat warning — stay indoors.");
    } else if (temperature < 0) {
        puts("Advisory: Freezing — bundle up.");
    } else {
        puts("Advisory: Moderate weather.");
    }

    return EXIT_SUCCESS;
}

// Thinking in C:
// C's if/else if/else evaluates conditions in order and
// executes the FIRST true branch, then skips the rest.
// There is no implicit boolean conversion to 0/1 in if
// conditions — expressions must evaluate to scalar types.
// This makes control flow predictable and explicit.
