/*
 * How do I free memory and avoid leaks?
 *
 * This file demonstrates correct free patterns, the danger of
 * double-free, and dangling pointers.
 *
 * Run under Valgrind to detect leaks:
 *   valgrind --leak-check=full ./free_valgrind
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    /* --- Correct pattern: allocate, use, free, NULL --- */
    char *msg = (char *)malloc(32);
    if (msg == NULL) {
        perror("malloc failed");
        return EXIT_FAILURE;
    }

    snprintf(msg, 32, "Hello from the heap!");
    puts(msg);

    free(msg);
    /* msg is now a dangling pointer — do not dereference it */

    /* --- Set pointer to NULL after free to prevent double-free --- */
    msg = NULL;  /* free(NULL) is safe and is a no-op */

    /* --- Leak example (commented out): memory never freed --- */
    // int *leak = (int *)malloc(100 * sizeof(int));
    // /* forgot: free(leak);  valgrind will report this */

    /* --- Another safe allocation + free --- */
    int *numbers = (int *)malloc(5 * sizeof(int));
    if (numbers == NULL) {
        perror("malloc failed");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < 5; i++) {
        numbers[i] = (int)i;
    }

    free(numbers);
    numbers = NULL;

    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// Every malloc must be freed. Valgrind catches leaks, use-after-free, and double-free.
