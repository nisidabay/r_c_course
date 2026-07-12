/*
 * Exercise 07 (CHALLENGE): Parse fstab lines with strtok
 *
 * Concept: Use strtok to split fstab-like lines into their 6 fields.
 *
 * Each line has fields separated by whitespace or tabs:
 *
 *   /dev/sda1  /mnt/data  ext4  defaults  0  2
 *
 * The 6 fields are: device, mount_point, fstype, options, dump, pass
 *
 * Learn from concept 07_strtok.c before attempting this challenge.
 *
 * Safe C Standard: fgets for input. snprintf for building output.
 * Compile with: gcc -std=c11 -Wall -Wextra -pedantic ex_07_challenge.c -o ex_07_challenge
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 256
#define MAX_FIELDS 6

int main(void) {
    /* Simulated fstab content — in a real program you'd fgets from a file */
    char *lines[] = {
        "# This is a comment — skip it",
        "",
        "/dev/sda1  /mnt/data  ext4  defaults  0  2",
        "/dev/sdb1  /home      ext4  noatime   0  2",
        "tmpfs      /tmp       tmpfs defaults  0  0",
        NULL
    };

    for (int i = 0; lines[i] != NULL; ++i) {
        /* Skip blank lines and comments */
        if (lines[i][0] == '\0' || lines[i][0] == '#') {
            printf("[SKIP] %s\n", lines[i]);
            continue;
        }

        /* Make a mutable copy — strtok modifies the string */
        char copy[BUFSZ];
        // FIX ME: copy lines[i] into copy using snprintf

        printf("[LINE] %s\n", lines[i]);

        /* Parse the 6 fields with strtok */
        char *fields[MAX_FIELDS];
        int field_count = 0;

        // FIX ME: call strtok with " \t" delimiters, store each
        // token in fields[field_count], increment field_count,
        // continue until NULL or MAX_FIELDS reached

        /* Print the parsed fields */
        printf("  ");
        for (int j = 0; j < field_count; ++j) {
            // FIX ME: print each field
            // Expected format: "device=%s  mount=%s  type=%s  ..."
        }
        printf("\n");
    }

    printf("\n--- Challenge complete! ---\n");
    printf("Used strtok with whitespace delimiters.\n");

    return EXIT_SUCCESS;
}
