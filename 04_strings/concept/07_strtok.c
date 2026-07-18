/*
 * 07_strtok.c — strtok for string splitting
 * Group 04 - Strings
 *
 * strtok breaks a string into tokens based on delimiter characters.
 * The first call takes the string to tokenize; subsequent calls pass
 * NULL.  strtok modifies the original string by replacing delimiters
 * with '\0' — it does NOT make copies.
 *
 * KEY WARNING: strtok is NOT reentrant (uses static internal state).
 * For multi-threaded code use strtok_r (POSIX) or strtok_s (C11).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char line[] = "apple,banana,cherry";

	printf("Original string: %s\n", line);

	/* ---- Tokenize ---- */
	char *tokens[10]; /* array to store token pointers */
	int index = 0;

	printf("\nTokens:\n");

	char *token = strtok(line, ",");
	while (token != NULL) {
		tokens[index++] = token;
		printf("  %s\n", token);
		token = strtok(NULL, ",");
	}

	/* ---- Show the side effect: strtok overwrites delimiters ---- */
	printf("\nOriginal string after strtok (delimiters replaced by '/'):\n  ");
	for (size_t i = 0; i < sizeof(line); i++) {
		putchar(line[i] ? line[i] : '/');
	}
	printf("\n");

	/* ---- Stored tokens still point into the modified line ---- */
	printf("\nStored tokens (still valid — point into modified line):\n");
	for (int i = 0; i < index; i++) {
		printf("  %s\n", tokens[i]);
	}

	return EXIT_SUCCESS;
}

// Thinking in C:
// strtok splits a string destructively — it replaces delimiters
// with '\0' in place.  The returned pointers point into the
// original string.  If you need the original string preserved,
// copy it first with strdup().  strtok has internal static state
// so only one tokenization can be active at a time — use strtok_r
// or strtok_s for nested or threaded splitting.
