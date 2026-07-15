/*
 * Exercise 05 — _Generic
 *
 * Use C11's _Generic to create a macro that works for multiple types.
 *
 * Expected output:
 *   42 is int
 *   3.14 is double
 *   Hello is char*
 *
 * Hints:
 *   - #define TYPE_NAME(x) _Generic((x), int: "int", double: "double", char*: "char*")
 *   - printf("42 is %s\n", TYPE_NAME(42));
 *   - printf("3.14 is %s\n", TYPE_NAME(3.14));
 *   - printf("Hello is %s\n", TYPE_NAME("Hello"));
 *   - #include <stdio.h>, <stdlib.h>
 */
