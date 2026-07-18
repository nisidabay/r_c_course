/*
 * Exercise 08 — strtok basics
 *
 * Tokenize "apple,banana,cherry,date" with strtok(",") and print each token.
 * strtok modifies the original string; the first call takes the string,
 * subsequent calls pass NULL.
 *
 * Expected output:
 *   Tokens:
 *     apple
 *     banana
 *     cherry
 *     date
 *
 * Hints:
 *   - char line[] = "apple,banana,cherry,date";
 *   - char *token = strtok(line, ",");
 *   - while (token != NULL) { printf("  %s\n", token); token = strtok(NULL, ","); }
 *   - #include <stdio.h>, <stdlib.h>, <string.h>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Your code here

    return EXIT_SUCCESS;
}
