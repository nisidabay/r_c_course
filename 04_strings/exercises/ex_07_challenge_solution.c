/*
 * Exercise 07 (CHALLENGE): Parse fstab lines with strtok — SOLUTION
 *
 * Concept: Use strtok to split fstab-like lines into their 6 fields.
 *
 * Each line has fields separated by whitespace or tabs:
 *
 *   /dev/sda1  /mnt/data  ext4  defaults  0  2
 *
 * The 6 fields are: device, mount_point, fstype, options, dump, pass
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 256
#define MAX_FIELDS 6

int main(void) {
    char *lines[] = {
        "# This is a comment — skip it",
        "",
        "/dev/sda1  /mnt/data  ext4  defaults  0  2",
        "/dev/sdb1  /home      ext4  noatime   0  2",
        "tmpfs      /tmp       tmpfs defaults  0  0",
        NULL
    };

    for (int i = 0; lines[i] != NULL; ++i) {
        if (lines[i][0] == '\0' || lines[i][0] == '#') {
            printf("[SKIP] %s\n", lines[i]);
            continue;
        }

        char copy[BUFSZ];
        snprintf(copy, sizeof(copy), "%s", lines[i]);

        printf("[LINE] %s\n", lines[i]);

        char *fields[MAX_FIELDS];
        int field_count = 0;

        char *token = strtok(copy, " \t");
        while (token != NULL && field_count < MAX_FIELDS) {
            fields[field_count++] = token;
            token = strtok(NULL, " \t");
        }

        printf("  ");
        for (int j = 0; j < field_count; ++j) {
            if (j == 0) printf("device=%s", fields[j]);
            else if (j == 1) printf("  mount=%s", fields[j]);
            else if (j == 2) printf("  type=%s", fields[j]);
            else if (j == 3) printf("  opts=%s", fields[j]);
            else if (j == 4) printf("  dump=%s", fields[j]);
            else if (j == 5) printf("  pass=%s", fields[j]);
        }
        printf("\n");
    }

    printf("\n--- Challenge complete! ---\n");
    printf("Used strtok with whitespace delimiters.\n");

    return EXIT_SUCCESS;
}
