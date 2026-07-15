/*
 * Exercise 02 — Function Pointers
 *
 * Create an array of function pointers for arithmetic operations and call one.
 *
 * Expected output:
 *   10 + 5 = 15
 *
 * Hints:
 *   - int add(int a, int b) { return a + b; }
 *   - int sub(int a, int b) { return a - b; }
 *   - int (*ops[])(int, int) = {add, sub};
 *   - int result = ops[0](10, 5);
 *   - #include <stdio.h>, <stdlib.h>
 */
