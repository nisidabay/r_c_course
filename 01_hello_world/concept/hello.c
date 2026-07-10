#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *greeting = "Hello, C World!";
    const int answer = 42;
    const char letter = 'Z';

    printf("String:  %s\n", greeting);
    printf("Integer: %d\n", answer);
    printf("Char:    %c  (ASCII %d)\n", letter, letter);
    printf("Hex:     0x%x  |  Width-5: [%5d]\n", answer, answer);

    printf("\n"
           "=== printf Format Quick Reference ===\n"
           "  %%s  -- print a string\n"
           "  %%d  -- print a signed integer\n"
           "  %%c  -- print a single character\n"
           "  %%x  -- print integer in lowercase hex\n"
           "  %%%%  -- print a literal percent sign\n"
           "  [%%5d] -- right-align in 5 columns\n"
           "====================================\n");

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * printf is your window into the program's state.  Every format
 * specifier tells printf both the type and the display style of
 * the argument.  Mismatch the specifier (e.g. %d for a double)
 * and the behaviour is undefined -- the compiler won't save you.
 * Get comfortable with the common ones early; you'll use them
 * in almost every debugging session.
 * ============================================================
 */

// 💡 Thinking in C:
// gcc -std=c11 -Wall -Wextra -pedantic -Werror turns on every safety check.
