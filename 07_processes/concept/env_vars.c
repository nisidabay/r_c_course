/*
 * How do I read environment variables?
 *
 * getenv("NAME") returns the value of the environment variable NAME,
 * or NULL if the variable does not exist.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *vars[] = {"HOME", "USER", "SHELL", "PATH", "LANG"};
    size_t n = sizeof(vars) / sizeof(vars[0]);

    for (size_t i = 0; i < n; i++) {
        const char *val = getenv(vars[i]);
        if (val != NULL) {
            printf("%s=%s\n", vars[i], val);
        } else {
            printf("%s=(unset)\n", vars[i]);
        }
    }

    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// getenv reads an environment variable. getenv can return NULL if the variable is not set.
