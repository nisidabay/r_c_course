/*
 * Exercise 01 — Heap vs Stack
 *
 * Allocate an int on the stack and an int on the heap. Compare their addresses.
 *
 * Expected output (addresses will vary):
 *   Stack address: 0x7fff...
 *   Heap address:  0x5555...
 *
 * Hints:
 *   - int stack_var = 42;
 *   - int *heap_var = malloc(sizeof(int));
 *   - *heap_var = 42;
 *   - printf with %p for addresses
 *   - free(heap_var) at the end
 *   - #include <stdlib.h>, <stdio.h>
 */
