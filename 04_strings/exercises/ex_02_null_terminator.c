/*
 * Exercise 02: The fragile '\0' sentinel
 *
 * Concept: C strings end with '\0' (null terminator). strlen() walks
 *          character by character until it finds '\0'. If '\0' is missing,
 *          strlen keeps reading past the buffer — undefined behavior.
 *
 * Fill in the blanks (marked BLANK) to complete a program that demonstrates:
 *   - strlen walking the string O(n)
 *   - Manual walk showing what strlen does internally
 *   - What happens when there's no null terminator
 *
 * Safe C Standard: no strcpy/strcat/sprintf/scanf/atoi/atof.
 * Compile with: gcc -std=c11 -Wall -Wextra -pedantic ex_02_null_terminator.c -o ex_02_null_terminator
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    char *greeting = "hello world how are you today";
    size_t len = strlen(greeting);

    printf("strlen(\"%s\") = %zu\n", greeting, len);
    printf("strlen walked %zu characters looking for '\\0'.\n\n", len);

    /* Manual walk — this is what strlen does internally */
    char *p = greeting;
    size_t walked = 0;
    while (*p != '\0') { // FIX ME
        ++walked;
        ++p;
    }
    printf("Manual walk found %zu chars before '\\0'. Same as strlen.\n\n", walked);

    /* Properly terminated buffer */
    char good_buf[4];
    good_buf[0] = 'H';
    good_buf[1] = 'i';
    good_buf[2] = '!';
    good_buf[3] = '\0'; // FIX ME
    printf("good_buf = \"%s\"  strlen = %zu  (fits because we left room)\n",
           good_buf, strlen(good_buf));

    /* Missing terminator — dangerous! */
    char bad_buf[4];
    bad_buf[0] = 'O';
    bad_buf[1] = 'o';
    bad_buf[2] = 'p';

    printf("\nWithout null terminator (bad_buf has no '\\0'):\n");
    printf("bad_buf = \"%s\"  <-- strlen keeps reading past the buffer!\n", bad_buf);
    printf("That printed garbage because strlen didn't find '\\0' inside our 4 bytes.\n");

    printf("\nLesson: null terminators are C's way of marking string end.\n");
    printf("But they're invisible, easy to forget, and O(n) to find.\n");

    return 0;
}
