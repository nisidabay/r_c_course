/*
 * Exercise 04 — Scope
 *
 * Show that variables declared inside a block {} are not visible outside.
 *
 * Expected output:
 *   Inside block: 10
 *   Outside block: 0
 *
 * Hints:
 *   - { int x = 10; printf("Inside block: %d\n", x); }
 *   - printf("Outside block: %d\n", x); — this will NOT compile
 *   - Declare x outside first, then show a different inner x shadows it
 *   - Or show that inner x is gone after the block
 */
