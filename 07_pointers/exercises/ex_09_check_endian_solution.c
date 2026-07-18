/*
 * ex_09_check_endian.c — SOLUTION
 * Group 06 — Pointers 101
 * Exercise 09: check endianness using *(char *)&num
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* 0x00000001 — least significant byte is 0x01 */
    int num = 1;

    /* Cast &num to char* and dereference to read the FIRST byte in memory */
    if (*(char *)&num == 1) {
        printf("Little Endian\n");
    } else {
        printf("Big Endian\n");
    }

    return EXIT_SUCCESS;
}
