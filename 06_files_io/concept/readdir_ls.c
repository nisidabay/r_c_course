/* How do I list a directory? */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(void) {
    const char *dirname = ".";
    DIR *dir = opendir(dirname);

    if (!dir) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    size_t count = 0;

    while ((entry = readdir(dir))) {
        if (entry->d_name[0] == '.')
            continue;
        printf("%s\n", entry->d_name);
        count++;
    }

    if (closedir(dir) == -1) {
        perror("closedir");
        return EXIT_FAILURE;
    }

    printf("\nTotal entries listed: %zu\n", count);
    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// readdir lists directory entries. Filter out dot and dot-dot yourself.
