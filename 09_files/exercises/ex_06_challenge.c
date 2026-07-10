/*
 * Mini-Challenge 06: File Reader — Line Count & Longest Line
 *
 * Concept: Read a text file, count the number of lines, and find the
 *          longest line (by character count, including \\n).
 *
 * Write a complete program that:
 *
 *   1. Opens a file called "sample.txt" for reading.
 *   2. Counts the total number of lines in the file.
 *   3. Finds the longest line (the line with the most characters).
 *   4. Prints:
 *        Total lines: N
 *        Longest line length: M
 *        Longest line: <the actual line>
 *
 * Rules:
 *   - Use fgets(buf, size, fp) for reading.
 *   - Use strlen() from <string.h> to measure line length.
 *   - fopen must always be checked — if it fails, print an error and return 1.
 *   - Assume no single line exceeds 1024 characters.
 *   - No scanf, no strcpy/strcat/sprintf/atoi/atof.
 *
 * HINT:
 *   - After fgets reads a line, strlen(line) gives its length.
 *   - If strlen(line) > current max, copy the line and update max.
 *   - Use a 2D char array or a separate buffer to store the longest line.
 *     char longest[1024];  and copy with a manual loop (no strcpy).
 *
 * Compile with: gcc -std=c11 -Wall -Wextra -pedantic ex_06_challenge.c -o ex_06_challenge
 */

#include <stdio.h>
#include <string.h>

#define MAX_LINE 1024

int main(void) {
    /* Your code below */

    return 0;
}
