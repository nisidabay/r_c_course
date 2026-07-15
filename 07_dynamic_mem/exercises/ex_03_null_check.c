/*
 * Exercise 03 — Null Check
 *
 * Always check malloc's return value before using the pointer.
 *
 * Expected output:
 *   Allocation succeeded: 1000 ints
 *
 * Hints:
 *   - int *arr = malloc(1000 * sizeof(int));
 *   - if (arr == NULL) { fprintf(stderr, "malloc failed\n"); return EXIT_FAILURE; }
 *   - printf("Allocation succeeded: 1000 ints\n");
 *   - free(arr);
 */
