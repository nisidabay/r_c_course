/*
 * 06b_array_of_pointers.c — Array of pointers to char (char *lines[])
 *
 * Tony Banters' "Strings Aren't Real" — Day 6b (Interlude)
 *
 * KEY INSIGHT: char *lines[] = { "one", "two", NULL } is an array whose
 * elements are POINTERS. Each points to a string literal. The compiler
 * counts the elements. NULL marks the end — no length variable needed.
 *
 * gcc -std=c11 -Wall -Wextra -pedantic 06b_array_of_pointers.c -o 06b_array_of_pointers
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	/* ---- Step 1: sizeof on array of pointers ---- */
	/* lines: array of char pointers, compiler-sized from initializer */
	char *lines[] = {"Alpha", "Beta", "Gamma", NULL};

	/* sizeof(lines) = total bytes of the array (4 pointers × 8 = 32) */
	printf("sizeof(lines) = %zu bytes  (entire array)\n", sizeof(lines));
	/* sizeof(lines[0]) = width of one pointer (always 8 on 64-bit) */
	printf("sizeof(lines[0]) = %zu bytes  (one pointer)\n", sizeof(lines[0]));
	/* element count = total bytes ÷ pointer width */
	printf("Element count = %zu  (includes NULL sentinel)\n", sizeof(lines) / sizeof(lines[0]));

	/* ---- Step 2: Iterate with NULL sentinel ---- */
	printf("\nArray of pointers:\n");
	for (int i = 0; lines[i] != NULL; ++i) {
		printf("  lines[%d] = \"%s\"\t(strlen = %zu)\n", i, lines[i], strlen(lines[i]));
	}

	/* ---- Step 3: Different-sized strings ---- */
	/* mixed: strings of varying lengths — each is a separate char* */
	char *mixed[] = {"a", "Hello, world!", "", "C11", NULL};

	printf("\nDifferent-sized strings:\n");
	for (int j = 0; mixed[j] != NULL; ++j) {
		/* sizeof(mixed[j]) is always 8 — pointer width */
		/* strlen(mixed[j]) varies — actual string length */
		printf("  mixed[%d] = \"%s\"\t(sizeof = %zu, strlen = %zu)\n", j, mixed[j],
		       sizeof(mixed[j]), strlen(mixed[j]));
	}

	printf("\n  Key insight: sizeof is always %zu (pointer width).\n", sizeof(mixed[0]));
	printf("  strlen varies — it measures the actual string length.\n");

	/* ---- Step 4: Empty array edge case ---- */
	/* empty: only the sentinel — no real strings */
	char *empty[] = {NULL};

	printf("\nEmpty array (just NULL):\n");
	printf("  sizeof(empty) = %zu bytes\n", sizeof(empty));

	int k;
	for (k = 0; empty[k] != NULL; ++k) {
		/* This body never executes — empty[0] IS NULL */
	}
	printf("  (Loop ran %d times — empty array handled gracefully.)\n", k);

	return EXIT_SUCCESS;
}

// Thinking in C:
// char *lines[] = { "a", "b", NULL } is an array of POINTERS, not strings.
// Each element is a char* (8 bytes), pointing to a string literal.
// NULL sentinel replaces a count variable — the loop stops when it hits NULL.
// sizeof(lines) gives total array bytes; sizeof(lines[0]) = 8 (pointer width).
// strlen walks the actual string — it's O(n), and each string can be a different length.
// This is the same pattern used by main(int argc, char *argv[]) and POSIX environ.
