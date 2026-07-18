/*
 * Exercise 07 — Challenge: Fstab Parser
 *
 * Parse fstab-like lines using strtok to split them into their 6 fields.
 * Each line has fields separated by whitespace or tabs:
 *
 *   /dev/sda1  /mnt/data  ext4  defaults  0  2
 *
 * The 6 fields are: device, mount_point, fstype, options, dump, pass
 *
 * Expected output:
 *   [SKIP] # This is a comment — skip it
 *   [SKIP]
 *   [LINE] /dev/sda1  /mnt/data  ext4  defaults  0  2
 *     device=/dev/sda1  mount=/mnt/data  type=ext4  opts=defaults  dump=0  pass=2
 *   ...
 *
 * Hints:
 *   - fgets not needed — use a pre-defined array of strings with NULL terminator
 *   - Skip lines starting with '#' or empty lines
 *   - strtok(copy, " \t") to split on space or tab
 *   - strtok modifies the string — work on a COPY
 *   - Store tokens in an array up to MAX_FIELDS (6)
 *   - Print each field with descriptive labels
 *   - #include <stdio.h>, <stdlib.h>, <string.h>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 256
#define MAX_FIELDS 6

int main(void)
{
    // Your code here

    return EXIT_SUCCESS;
}
