/*
 * ex_01_enums_switch_solution.c
 * Group 10 — Advanced
 * Exercise 01: enums and switch — SOLUTION
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    COLOUR_COUNT   /* sentinel — not a real colour */
} Colour;

const char *colour_name(Colour c) {
    switch (c) {
        case RED:    return "Red";
        case GREEN:  return "Green";
        case BLUE:   return "Blue";
        case YELLOW: return "Yellow";
        default:     return "???";
    }
}

int is_primary(Colour c) {
    switch (c) {
        case RED:
        case BLUE:
        case GREEN:
            return 1;
        default:
            return 0;
    }
}

int main(void) {
    for (int i = 0; i < COLOUR_COUNT; i++) {
        Colour c = (Colour)i;
        const char *name = colour_name(c);
        int primary = is_primary(c);
        printf("Colour %d: %-8s  primary=%d\n", i, name, primary);
    }
    return EXIT_SUCCESS;
}
