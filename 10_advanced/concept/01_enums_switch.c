/*
 * File:  01_enums_switch.c
 * Group: 10 — Paradigm Shift: Enums & Switch (Advanced)
 *
 * Concept: enum types + switch/case pattern matching
 *
 * Shows:
 *   - Declaring an enum with named constants (Day)
 *   - Using switch/case to branch on enum values
 *   - A lookup function that maps an enum to a string
 *   - Combining structs (from group 01), arrays (group 03), and
 *     snprintf (the safe replacement for sprintf)
 *
 * Build:  gcc -std=c11 -Wall -Wextra -pedantic 01_enums_switch.c -o 01_enums_switch
 * Run:    ./01_enums_switch
 */

#include <stdio.h>
#include <stdlib.h>

/* ---------- enum definition ---------- */
typedef enum {
    MONDAY,     /* 0 */
    TUESDAY,    /* 1 */
    WEDNESDAY,  /* 2 */
    THURSDAY,   /* 3 */
    FRIDAY,     /* 4 */
    SATURDAY,   /* 5 */
    SUNDAY,     /* 6 */
    DAY_COUNT   /* 7 — sentinel, not a real day */
} Day;

/* ---------- helper struct (group 01: structs) ---------- */
typedef struct {
    Day   day;
    int   temp_c;       /* average temperature for that day */
    char  note[64];
} DayInfo;

/* ---------- enum → string via switch ---------- */
const char *day_name(Day d) {
    switch (d) {
        case MONDAY:    return "Monday";
        case TUESDAY:   return "Tuesday";
        case WEDNESDAY: return "Wednesday";
        case THURSDAY:  return "Thursday";
        case FRIDAY:    return "Friday";
        case SATURDAY:  return "Saturday";
        case SUNDAY:    return "Sunday";
        default:        return "???";
    }
}

int main(void) {
    /* array of structs (group 03) — one entry per weekday */
    DayInfo week[] = {
        { MONDAY,    22, "Start of work week"  },
        { TUESDAY,   24, "Productivity peak"   },
        { WEDNESDAY, 21, "Hump day"            },
        { THURSDAY,  23, "Almost there"        },
        { FRIDAY,    25, "Weekend eve"         },
    };
    size_t count = sizeof week / sizeof week[0];

    char buf[128];

    for (size_t i = 0; i < count; i++) {
        /* snprintf (group 07) — safe string building, no sprintf */
        snprintf(buf, sizeof buf,
                 "Day %zu: %-10s  %2d°C  — %s",
                 i + 1,
                 day_name(week[i].day),
                 week[i].temp_c,
                 week[i].note);

        printf("%s\n", buf);
    }

    return EXIT_SUCCESS;
}

/*
 * Thinking in C — Group 10
 *
 * Enums give names to magic numbers; switch/case turns those names into
 * structured branches.  Together they replace chains of if/else with a
 * readable dispatch table — the compiler can even warn about missing cases.
 * This is C's lightweight answer to tagged unions / sum types.
 */
