/* How do I write to a file? */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *filename = "output.txt";
    FILE *fp = fopen(filename, "w");

    if (!fp) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    if (fputs("Hello, file!\n", fp) == EOF) {
        perror("fputs");
        fclose(fp);
        return EXIT_FAILURE;
    }

    if (fprintf(fp, "Line number: %d\n", 42) < 0) {
        perror("fprintf");
        fclose(fp);
        return EXIT_FAILURE;
    }

    if (fclose(fp) == EOF) {
        perror("fclose");
        return EXIT_FAILURE;
    }

    printf("Successfully wrote to '%s'.\n", filename);
    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// fwrite and fprintf write to files. Always check return values and close after writing.
