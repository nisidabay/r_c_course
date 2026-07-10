#include <stdio.h>

int main(void) {
    int age = 22;
    int has_license = 1;
    int has_insurance = 0;

    puts("Rental Car Eligibility\n");

    if (age >= 21 && has_license) {
        puts("Can rent a car — age and license OK.");
    } else {
        puts("Cannot rent — either too young or no license.");
    }

    if (!has_insurance) {
        puts("Warning: No insurance on file. Rental denied.\n");
    }

    int temp = 35;
    int is_raining = 1;

    puts("Beach Day Checker:");
    if (temp > 25 && !is_raining) {
        puts("Perfect beach weather!");
    } else if (temp > 25 || (temp > 15 && !is_raining)) {
        puts("Decent day — possible beach trip.");
    } else {
        puts("Stay inside.");
    }

    int completed_course = 0;
    int has_exemption = 1;

    printf("\nCourse prerequisite: %s\n",
           completed_course || has_exemption
               ? "Eligible to enroll"
               : "Prerequisite not met");

    return 0;
}

// Thinking in C:
// && and || short-circuit: the right side only evaluates
// if needed. ! flips truth value — non-zero becomes 0,
// zero becomes 1. Logical operators treat any non-zero
// value as true and produce int results (1 or 0).
