/*
 * 12_check_endian.c — Endianness: inspecting memory layout
 * Group 06 - Pointers 101
 *
 * Endianness describes the byte order of multi-byte values in memory.
 *   Little-endian: least significant byte at the lowest address (x86/x64)
 *   Big-endian:    most significant byte at the lowest address (network order)
 *
 * We use *(char *)&num to re-interpret the integer's first byte as a
 * character — exposing the in-memory byte order.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* 0x00000001 — least significant byte is 0x01 */
    int num = 1;

    /* Cast &num to char* and dereference to read the FIRST byte */
    if (*(char *)&num == 1) {
        printf("Little Endian\n");
    } else {
        printf("Big Endian\n");
    }

    /* Show the byte layout of a 4-byte int */
    unsigned int val = 0x01020304;
    unsigned char *bytes = (unsigned char *)&val;

    printf("\nByte layout of 0x01020304:\n");
    for (size_t i = 0; i < sizeof(val); i++) {
        printf("  byte %zu: 0x%02x\n", i, bytes[i]);
    }

    if (bytes[0] == 0x04) {
        printf("Confirms: Little Endian (LSB first)\n");
    } else if (bytes[0] == 0x01) {
        printf("Confirms: Big Endian (MSB first)\n");
    } else {
        printf("Unknown byte order.\n");
    }

    return EXIT_SUCCESS;
}

// Thinking in C:
// Endianness matters when you read/write binary data across
// systems (files, network protocols).  The idiom *(char *)&num
// casts an int's address to a byte pointer, letting you inspect
// individual bytes.  x86/x64 is little-endian; network byte
// order (big-endian) is the convention for Internet protocols.
// Always be explicit about endianness in binary formats.
