#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char name[32];
    char age_str[5];  // 3 digits + newline + null → max plausible age 122

    printf("Enter your name: ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        fprintf(stderr, "Error reading input or EOF reached\n");
        return EXIT_FAILURE;
    }

    // fgets keeps the trailing newline — remove it
    name[strcspn(name, "\n")] = '\0';

    printf("Enter your age: ");
    if (fgets(age_str, sizeof(age_str), stdin) == NULL) {
        fprintf(stderr, "Error reading input or EOF reached\n");
        return EXIT_FAILURE;
    }

    age_str[strcspn(age_str, "\n")] = '\0';

    // strtol parses a string into a long with full error detection.
    char *endptr;
    errno = 0;
    long age = strtol(age_str, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Age out of range\n");
        return EXIT_FAILURE;
    }
    if (endptr == age_str || *endptr != '\0') {
        fprintf(stderr, "Invalid input: expected a whole number\n");
        return EXIT_FAILURE;
    }
    if (age < 0 || age > 150) {
        fprintf(stderr, "Age out of reasonable range\n");
        return EXIT_FAILURE;
    }

    printf("Hello, %s! You are %ld years old.\n", name, age);

    return EXIT_SUCCESS;
}

// Thinking in C:
// C has no built-in input mechanism — fgets reads raw text from stdin.
//
// `stdin` is a predefined stream in C that represents standard input. This
// could be the keyboard for interactive programs or another file if you're
// redirecting input from a file.
//
// fgets reads up to the buffer size or until a newline, whichever comes
// first. It includes the newline in the buffer. We strip it with strcspn,
// which finds the position of '\n' so we can replace it with '\0'.
//
// strtol is the safe way to convert a string to a number. It reports parse
// errors through the endptr pointer: if endptr == age_str after the call, no
// digits were consumed (not a number). We also check errno for ERANGE to
// detect overflow.
//
// With properly sized buffers (64+ bytes), the entire input line almost
// always fits in a single fgets call, so no consume_remaining is needed.
//
// Always check the return value of fgets. It returns NULL when stdin
// reaches end-of-file or a read error occurs.
