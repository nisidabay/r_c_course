/*
 * Exercise 08 — strtok basics — SOLUTION
 *
 * Tokenize "apple,banana,cherry,date" with strtok(",") and print each token.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char line[] = "apple,banana,cherry,date";

    printf("Tokens:\n");
    char *token = strtok(line, ",");
    while (token != NULL) {
        printf("  %s\n", token);
        token = strtok(NULL, ",");
    }

    return EXIT_SUCCESS;
}
