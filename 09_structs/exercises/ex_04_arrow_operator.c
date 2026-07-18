/*
 * Exercise 04 — Arrow Operator
 *
 * Use the arrow operator (->) to access struct members through a pointer.
 *
 * Expected output:
 *   Circle at (10, 20) with radius 5
 *
 * Hints:
 *   - typedef struct { int x; int y; int r; } Circle;
 *   - Circle c = {10, 20, 5};
 *   - Circle *ptr = &c;
 *   - ptr->x, ptr->y, ptr->r  (equivalent to (*ptr).x)
 */
