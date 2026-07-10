/*
 * 02_null_terminator.c — The fragile '\0' sentinel
 *
 * Tony Banters' "Strings Aren't Real" — Day 2
 *
 * KEY INSIGHT: C strings end with '\0' (null terminator).
 * strlen() walks character-by-character until it finds '\0'.
 * If '\0' is missing, strlen keeps reading past the buffer.
 * If you forget room for '\0', you get buffer overflow.
 *
 * gcc -std=c11 -Wall -Wextra -pedantic 02_null_terminator.c -o 02_null_terminator
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    /* strlen must walk the whole string — O(n) */
    char *greeting = "hello world how are you today";
    size_t len = strlen(greeting);
    printf("strlen(\"%s\") = %zu\n", greeting, len);
    printf("strlen walked %zu characters looking for '\\0'.\n\n", len);

    /* Demo: manually walk until '\0' — this is what strlen does */
    char *p = greeting;
    size_t walked = 0;
    while (*p != '\0') {
        ++walked;
        ++p;
    }
    printf("Manual walk found %zu chars before '\\0'. Same as strlen.\n\n", walked);

    /* The danger: forgetting room for '\0' causes buffer overflow */
    char small_buf[4];                          /* room for only 3 chars + \0 */
    /* Copying "hello" (5 chars) into a 4-byte buffer would overflow.
     * Instead, let's construct by hand to show the problem: */
    small_buf[0] = 'H';
    small_buf[1] = 'i';
    small_buf[2] = '!';
    small_buf[3] = '\0';   /* MUST fit — if we omitted this, no terminator! */

    printf("small_buf = \"%s\"  strlen = %zu  (fits because we left room)\n",
           small_buf, strlen(small_buf));

    /* Without terminator, functions don't know where the string ends */
    char no_term[4];
    no_term[0] = 'O';
    no_term[1] = 'o';
    no_term[2] = 'p';
    /* no_term[3] is uninitialized — no '\0' set */

    printf("\nWithout null terminator (no_term has no '\\0'):\n");
    printf("no_term = \"%s\"  <-- strlen keeps reading past the buffer!\n", no_term);
    printf("That printed garbage because strlen didn't find '\\0' inside our 4 bytes.\n");

    printf("\nLesson: null terminators are C's way of marking string end.\n");
    printf("But they're invisible, easy to forget, and O(n) to find.\n");

    return 0;
}

// Thinking in C:
// '\0' is a sentinel value — C functions use it to know where text ends.
// strlen is O(n) because it must scan every byte until it hits '\0'.
// Forgetting room for '\0' or forgetting to write it causes buffer overflows.
// The sentinel approach is memory-efficient but fragile and slow.
