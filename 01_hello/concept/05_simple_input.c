#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * consume_remaining — discard characters left in stdin after fgets
 * truncates a line.  Only call when you detect truncation.
 */
static void consume_remaining(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main(void) {
    char name[32];
    char age_str[5];  // 3 digits + newline + null → max plausible age 122

    printf("Enter your name: ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        fprintf(stderr, "Error reading input or EOF reached\n");
        return 1;
    }

    // If the input was longer than 31 chars, flush the rest from stdin
    size_t len = strlen(name);
    if (len > 0 && name[len - 1] != '\n')
        consume_remaining();

    // fgets keeps the trailing newline — remove it by replacing '\n' with '\0'
    name[strcspn(name, "\n")] = '\0';

    printf("Enter your age: ");
    if (fgets(age_str, sizeof(age_str), stdin) == NULL) {
        fprintf(stderr, "Error reading input or EOF reached\n");
        return 1;
    }

    len = strlen(age_str);
    if (len > 0 && age_str[len - 1] != '\n')
        consume_remaining();

    // strtol parses a string into a long with full error detection.
    // endptr points to the first character NOT consumed by the parse.
    // Don't worry if pointers feel strange right now —
    // Group 06 is dedicated to mastering them. For now,
    // just trust the pattern: strtol + endptr = safe parsing.
    char *endptr;
    long age = strtol(age_str, &endptr, 10);

    // Validate: the parse must consume at least one digit, and the
    // remaining character must be the newline we expect from fgets.
    if (endptr == age_str || *endptr != '\n') {
        fprintf(stderr, "Invalid input: expected a whole number\n");
        return 1;
    }

    printf("Hello, %s! You are %ld years old.\n", name, age);

    return 0;
}

// Thinking in C:
// C has no built-in input mechanism — fgets reads raw text from stdin.
//
// `stdin` is a predefined stream in C that represents standard input. This
// could be the keyboard for interactive programs or another file if you're
// redirecting input from a file.
//
// fgets reads up to the buffer size or until a newline, whichever comes
// first. It includes the newline in the buffer. We strip it from the name
// with strcspn, which finds the position of '\n' so we can replace it with
// '\0' (the null terminator).
//
// **But here's the catch.** If the user types more than 31 characters for
// their name, fgets reads only the first 31 and leaves the rest in stdin.
// The next fgets (for the age) would read that leftover garbage instead of
// the age. That's what consume_remaining prevents.
//
// The detection is: after fgets, check `buf[len-1] != '\n'`. If there's no
// newline at the end, the line didn't fit. Call consume_remaining() to drain
// stdin until the next newline or EOF. Then the next fgets starts fresh.
//
// This guard goes AFTER every fgets and BEFORE the next read. Without it, a
// user who types a long line silently corrupts every following input.
//
// strtol is the safe way to convert a string to a number. It reports parse
// errors through the endptr pointer: if endptr == age_str after the call, no
// digits were consumed (not a number). This is how you validate numeric
// input in modern C — no undefined behavior, no silent garbage.
//
// Always check the return value of fgets. It returns NULL when stdin
// reaches end-of-file or a read error occurs.
