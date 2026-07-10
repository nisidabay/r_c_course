/* How do I read a file line by line? */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *filename = "example.txt";
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    char buf[1024];
    size_t line_count = 0;

    while (fgets(buf, sizeof buf, fp)) {
        line_count++;
        printf("Line %zu: %s", line_count, buf);
    }

    if (ferror(fp)) {
        perror("fgets");
        fclose(fp);
        return EXIT_FAILURE;
    }

    printf("\nTotal lines read: %zu\n", line_count);

    fclose(fp);
    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// fgets reads a line safely with a size limit. It keeps the newline if there is room.
