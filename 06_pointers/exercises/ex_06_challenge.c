/*
 * Exercise 06 — Challenge: Reverse Array in Place
 *
 * Reverse an integer array using pointers (no array indexing).
 *
 * Expected output:
 *   Before: 1 2 3 4 5
 *   After:  5 4 3 2 1
 *
 * Hints:
 *   - int arr[] = {1, 2, 3, 4, 5}; int n = 5;
 *   - int *start = arr; int *end = arr + n - 1;
 *   - while (start < end) swap *start and *end, then start++, end--
 *   - Write a helper: void swap(int *a, int *b)
 */
