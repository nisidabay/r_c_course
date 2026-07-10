/* How do I get file metadata? */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void) {
    const char *filename = "example.txt";
    struct stat st;

    if (stat(filename, &st) == -1) {
        perror("stat");
        return EXIT_FAILURE;
    }

    printf("File:        %s\n", filename);
    printf("Size:        %lld bytes\n", (long long)st.st_size);
    printf("Mode:        %o\n", (unsigned)st.st_mode & 0777);
    printf("Is regular:  %s\n", S_ISREG(st.st_mode) ? "yes" : "no");

    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// stat gets file metadata: size, type, permissions. Check the return value.
