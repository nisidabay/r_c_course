/*
 * Exercise 02 — Power of 2 check — SOLUTION
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_power_of_two(unsigned int n)
{
    if (n == 0)
        return 0;
    return (n & (n - 1)) == 0;
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
    unsigned long val = strtoul(buf, &endptr, 10);
    if (endptr == buf || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;

    if (is_power_of_two(n))
        printf("%u is a power of 2\n", n);
    else
        printf("%u is NOT a power of 2\n", n);

    return EXIT_SUCCESS;
}
