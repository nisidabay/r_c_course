/*
 * Exercise 03 — Bit mask (check a specific bit) — SOLUTION
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_bit_set(unsigned int n, int i)
{
    return (n >> i) & 1;
}

static void print_bits(unsigned int n)
{
    for (int i = 31; i >= 0; i--) {
        putchar((n >> i) & 1 ? '1' : '0');
        if (i > 0 && i % 8 == 0)
            putchar(' ');
    }
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

    printf("Enter bit position (0-31): ");
    if (fgets(buf, sizeof buf, stdin) == NULL)
        return EXIT_FAILURE;

    len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    } else if (len > 0) {
        buf[len - 1] = '\0';
    }

    long pos = strtol(buf, &endptr, 10);
    if (endptr == buf || *endptr != '\0' || pos < 0 || pos > 31) {
        fprintf(stderr, "Invalid position (must be 0-31)\n");
        return EXIT_FAILURE;
    }

    printf("%u in binary: ", n);
    print_bits(n);
    printf("\n");

    if (is_bit_set(n, (int)pos))
        printf("Bit %ld is SET (value: %lu)\n", pos, 1UL << pos);
    else
        printf("Bit %ld is NOT set\n", pos);

    return EXIT_SUCCESS;
}
