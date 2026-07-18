/*
 * Exercise 06 — Safe Building
 *
 * Build strings safely with snprintf (bounded output) and strdup
 * (checked allocation). Always avoid buffer overflow.
 *
 * Expected output:
 *   snprintf result:
 *     Needed: 34 characters (would need 35-byte buffer for full output)
 *     Wrote:  "Hello Alice, you have 42 messages."
 *
 *   strdup result:
 *     Original: "This text needs to be copied to a new location."  (at 0x...)
 *     Copy:     "This text needs to be copied to a new location."  (at 0x...)
 *     Different addresses -> copy IS a real, independent allocation.
 *     Modified copy: "this text needs to be copied to a new location."  (original unchanged)
 *
 *   Constructed path: "/home/alice/documents/report.txt"
 *
 * Hints:
 *   - #define _POSIX_C_SOURCE 200809L before includes (for strdup)
 *   - #include <stddef.h>, <stdio.h>, <stdlib.h>, <string.h>
 *   - snprintf(buf, sizeof(buf), "format", ...) — ALWAYS bound the output
 *   - snprintf returns what it WOULD have written (excluding '\0')
 *   - strdup(src) — returns NULL if malloc fails, ALWAYS check
 *   - free() what you strdup()
 */

#define _POSIX_C_SOURCE 200809L   /* for strdup (POSIX.1-2008) */

#include <stddef.h>   // size_t
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Your code here

    return EXIT_SUCCESS;
}
