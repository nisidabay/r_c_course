/*
 * Exercise 06 — Bitwise Calculator (Challenge)
 *
 * Write a program that reads an expression like "42 & 25" or
 * "128 << 3" and prints the result in both decimal and binary.
 *
 * Supported operators: & | ^ << >>
 *
 * Expected interaction:
 *   Enter expression: 42 & 25
 *   42          =  00000000 00000000 00000000 00101010
 *   25          =  00000000 00000000 00000000 00011001
 *   42 & 25 = 8 =  00000000 00000000 00000000 00001000
 *
 *   Enter expression: 1 << 10
 *   1           =  00000000 00000000 00000000 00000001
 *   10
 *   1 << 10 = 1024 =  00000000 00000000 00000100 00000000
 *
 * Hints:
 *   - Read a line with fgets, parse numbers with strtoul
 *   - Read the operator character(s) manually between the two numbers
 *   - Use strcmp on the operator string (& | ^ << >>)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
