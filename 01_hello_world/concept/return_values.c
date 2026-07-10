/*
 * How do I return values from main?
 *
 * The operating system reads main's return value as the program's
 * exit code.  Convention:
 *   0 (EXIT_SUCCESS) -- everything went fine.
 *   non-zero (EXIT_FAILURE) -- something went wrong.
 *   Other integers may encode specific error codes.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <your-name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("Hello, %s!\n", argv[1]);
    printf("argc == %d  (program name + %d argument(s))\n", argc, argc - 1);
    printf("EXIT_SUCCESS == %d\n", EXIT_SUCCESS);
    printf("EXIT_FAILURE == %d\n", EXIT_FAILURE);

    const int code = EXIT_SUCCESS;
    return code;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * Every program returns a status code to the operating system.
 * Shell scripts, Makefiles, and CI pipelines check this code to
 * decide whether a step succeeded or failed.  EXIT_SUCCESS and
 * EXIT_FAILURE are the portable way to express it; magic numbers
 * (0 / 1) work but obscure intent.
 * ============================================================
 */

// 💡 Thinking in C:
// EXIT_SUCCESS (0) and EXIT_FAILURE (1) tell the shell if your program worked.
