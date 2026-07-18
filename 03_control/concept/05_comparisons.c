#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int a = 10;
    int b = 20;
    int c = 10;

    puts("Comparison Operators\n");

    printf("a = %d, b = %d, c = %d\n\n", a, b, c);

    printf("a == c  -> %d  (equal)\n", a == c);
    printf("a == b  -> %d\n", a == b);
    printf("a != b  -> %d  (not equal)\n", a != b);
    printf("a != c  -> %d\n", a != c);
    printf("a <  b  -> %d  (less than)\n", a < b);
    printf("a >  b  -> %d  (greater than)\n", a > b);
    printf("a <= c  -> %d  (less than or equal)\n", a <= c);
    printf("b >= c  -> %d  (greater than or equal)\n\n", b >= c);

    double score = 89.5;
    double passing = 60.0;

    puts("Grade Check:");
    if (score >= passing) {
        printf("Score %.1f meets or exceeds %.1f\n", score, passing);
    }
    if (score == 100.0) {
        puts("Perfect score!");
    } else if (score > 90.0) {
        puts("Near perfect.");
    }

    return EXIT_SUCCESS;
}

// Thinking in C:
// Comparison operators return int — 1 for true, 0 for false.
// == checks equality (not assignment), while = assigns.
// Mixing = and == is a common C pitfall (assignment is an
// expression). Use double for comparisons sparingly;
// floating-point == can behave unexpectedly.
