/*
 * Exercise 01 — Count set bits (popcount) — SOLUTION
 *
 * Counts how many bits are 1 in an unsigned int.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static void print_bits(unsigned int n)
{
    for (int i = 31; i >= 0; i--) {
        putchar((n >> i) & 1 ? '1' : '0');
        if (i > 0 && i % 8 == 0)
            putchar(' ');
    }
}

static int popcount(unsigned int n)
{
    int count = 0;
    while (n) {
        n &= (n - 1);   /* clear the lowest set bit */
        count++;
    }
    return count;
}

int main(void)
{
    char buf[64];

    printf("Enter a number: ");
    if (fgets(buf, sizeof buf, stdin) == NULL)
        return EXIT_FAILURE;

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    } else if (len > 0) {
        buf[len - 1] = '\0';
    }

    char *endptr;
    errno = 0;
    unsigned long val = strtoul(buf, &endptr, 10);
    if (errno == ERANGE || endptr == buf || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;

    printf("%u in binary: ", n);
    print_bits(n);
    printf("\n");
    printf("Set bits: %d\n", popcount(n));

    return EXIT_SUCCESS;
}
