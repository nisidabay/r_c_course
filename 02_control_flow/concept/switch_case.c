/*
 * How do I select among multiple values with switch?
 *
 * switch compares an integer expression against a set of
 * constant labels.  A break ends each case; without it
 * execution falls through to the next label.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const int day = 3;   /* 1=Monday ... 7=Sunday */

    switch (day) {
        case 1:
            printf("Monday\n");
            break;
        case 2:
            printf("Tuesday\n");
            break;
        case 3:
            printf("Wednesday\n");
            break;
        case 4:
            printf("Thursday\n");
            break;
        case 5:
            printf("Friday\n");
            break;
        case 6:
            printf("Saturday\n");
            break;
        case 7:
            printf("Sunday\n");
            break;
        default:
            printf("Unknown day: %d\n", day);
            break;
    }

    /* Fall-through is sometimes useful */
    const char grade = 'B';

    switch (grade) {
        case 'A':
        case 'B':
        case 'C':
            printf("Passing grade.\n");
            break;
        case 'D':
        case 'F':
            printf("Failing grade.\n");
            break;
        default:
            printf("Invalid grade.\n");
            break;
    }

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * switch only works with integer types (int, char, enum).
 * Strings and floating-point values require if/else chains.
 * Always include a default case, even if it's empty, to
 * document that you considered unhandled values.  Missing
 * break is the most common switch bug -- some teams enforce
 * a deliberate annotation on intentional fall-throughs.
 * ============================================================
 */


// 💡 Thinking in C:
// switch works with integers. Each case needs break to avoid fall-through.
