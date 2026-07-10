/*
 * Exercise 01: Reverse a string
 *
 * Modify this example so that the program reads a string and
 * prints it reversed.
 *
 * Hint: swap characters from both ends moving inward. The loop
 * condition and body are blank -- fill them in.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char text[] = "Hello, C Programming!";
    const size_t len = strlen(text);

    printf("Original: %s\n", text);

    /* ---- YOUR LOOP HERE ---- */
    /* Swap characters from both ends: text[i] <-> text[len-1-i] */
    /* Fill in the loop header and body below */

    for (size_t i = 0; i < len / 2; i++) {
        char tmp = text[i];
        text[i] = text[len - 1 - i];
        text[len - 1 - i] = tmp;
    }

    printf("Reversed: %s\n", text);

    return EXIT_SUCCESS;
}
