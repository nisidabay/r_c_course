/*
 * ex_01_enums_switch.c
 * Group 10 — Advanced
 * Exercise 01: enums and switch
 *
 * Fill in the blanks (marked with /* @FILL_ME */) to complete the program.
 * Read the comments to understand what each line should do.
 */

#include <stdio.h>

/* ---------- enum definition ---------- */
typedef enum {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    /* @FILL_ME */   /* sentinel — not a real colour */
} Colour;

/* ---------- enum → string via switch ---------- */
const char *colour_name(Colour c) {
    switch ( /* @FILL_ME */ ) {
        case RED:    return "Red";
        case GREEN:  return "Green";
        case BLUE:   return "Blue";
        case YELLOW: return "Yellow";
        /* @FILL_ME */ : return "???";
    }
}

/* ---------- is the colour a primary colour? ---------- */
int is_primary(Colour c) {
    switch (c) {
        case RED:
        case BLUE:
        case /* @FILL_ME */:
            return 1;
        default:
            return 0;
    }
}

int main(void) {
    /* iterate over all colours except the sentinel */
    for (int i = 0; i < /* @FILL_ME */; i++) {
        Colour c = (Colour)i;
        const char *name = colour_name(c);
        int primary = is_primary(c);

        printf("Colour %d: %-8s  primary=%d\n", i, name, primary);
    }

    return 0;
}
