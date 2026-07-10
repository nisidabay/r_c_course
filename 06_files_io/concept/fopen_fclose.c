/* How do I open and close files? */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *filename = "example.txt";
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    printf("File '%s' opened successfully.\n", filename);

    if (fclose(fp) == EOF) {
        perror("fclose");
        return EXIT_FAILURE;
    }

    printf("File closed successfully.\n");
    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// fopen returns NULL on failure. Always check it. fclose releases the resource.
