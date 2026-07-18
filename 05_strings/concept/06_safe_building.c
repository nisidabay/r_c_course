/*
 * 06_safe_building.c — Safe string construction when you DO need to copy
 *
 * Tony Banters' "Strings Aren't Real" — Day 6
 *
 * KEY INSIGHT: Zero-copy slicing is great when you can keep the
 * original memory alive. But sometimes you NEED a real copy:
 * - constructing formatted output (use snprintf, NOT sprintf)
 * - duplicating strings (use strdup with NULL check)
 *
 * strdup requires _POSIX_C_SOURCE (or we could malloc+memcpy manually).
 *
 * gcc -std=c11 -Wall -Wextra -pedantic 06_safe_building.c -o 06_safe_building
 */

#define _POSIX_C_SOURCE 200809L /* for strdup (POSIX.1-2008) */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	/* --- snprintf: safe formatted construction --- */
	char greeting[64];
	char *name = "Alice";
	int count = 42;

	/* snprintf writes AT MOST sizeof(greeting)-1 chars, then always null-terminates.
	 * Returns how many characters it WOULD have written (excluding \0) if space were unlimited.
	 * If return >= sizeof(buf), output was truncated — you can detect it. */
	int needed = snprintf(greeting, sizeof(greeting), "Hello %s, you have %d messages.", name,
			      count);

	printf("snprintf result:\n");
	printf("  Needed: %d characters (would need %zu-byte buffer for full output)\n", needed,
	       (size_t)needed + 1);
	printf("  Wrote:  \"%s\"\n", greeting);

	if ((size_t)needed >= sizeof(greeting)) {
		printf("  (Output was TRUNCATED — buffer too small)\n");
	}

	/* --- strdup: safe duplication with NULL check --- */
	char *original = "This text needs to be copied to a new location.";
	char *copy = strdup(original);

	/* strdup returns NULL if malloc fails — ALWAYS check */
	if (!copy) {
		perror("strdup");
		return EXIT_FAILURE;
	}

	printf("\nstrdup result:\n");
	printf("  Original: \"%s\"  (at %p)\n", original, (void *)original);
	printf("  Copy:     \"%s\"  (at %p)\n", copy, (void *)copy);
	printf("  Different addresses -> copy IS a real, independent allocation.\n");

	/* Modify the copy — safe because it's our own memory */
	copy[0] = 't';
	printf("  Modified copy: \"%s\"  (original unchanged)\n", copy);

	/* Always free what strdup gave you */
	free(copy);

	/* --- snprintf for path construction --- */
	char path[256];
	char *dir = "/home/alice";
	char *file = "documents/report.txt";

	snprintf(path, sizeof(path), "%s/%s", dir, file);
	printf("\nConstructed path: \"%s\"\n", path);

	printf("\nSafe building rules:\n");
	printf("  1. snprintf(buf, sizeof(buf), ...) — always bound the output\n");
	printf("  2. strdup(src) — but ALWAYS check for NULL return\n");
	printf("  3. free() what you strdup() — ownership is now yours\n");

	return EXIT_SUCCESS;
}

// Thinking in C:
// strdup = malloc(strlen(src)+1) + memcpy. It's the safe way to copy strings.
// snprintf is the ONLY safe formatting function — sprintf has no size limit.
// Ownership matters: slice (borrowed pointer) vs strdup (owned allocation).
// The data+len pattern is for zero-copy views; snprintf/strdup are for when
// you actually need to own the memory.
