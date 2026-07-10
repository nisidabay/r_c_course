/*
 * Exercise 07 (CHALLENGE): Mini fstab-like line parser
 *
 * Concept: Build a mini parser that processes fstab-like lines using
 *          String_Slice operations. Each line has fields separated by
 *          whitespace or tabs:
 *
 *            /dev/sda1  /mnt/data  ext4  defaults  0  2
 *
 *          Your task is to write a function that parses a line and
 *          extracts each field using slice_take and slice_drop.
 *          No strtok, no strcpy, no strcmp — use String_Slice operations.
 *
 *          fstab reference: each line contains:
 *            <device>  <mount_point>  <fstype>  <options>  <dump>  <pass>
 *
 *          Comments (lines starting with '#') and blank lines should be skipped.
 *
 * This is a CHALLENGE — you'll need to combine everything you've learned:
 *   - String_Slice struct and constructor
 *   - slice_eq for comparing fields
 *   - slice_starts_with for detecting comments
 *   - slice_take and slice_drop for field extraction
 *
 * Note: Exercises 03+ use size_t (from <stddef.h>).
 *
 * Safe C Standard: no strcpy/strcat/sprintf/scanf/atoi/atof.
 *   fgets for reading line input. snprintf for building output.
 *   No strtok, no strcmp.
 * Compile with: gcc -std=c11 -Wall -Wextra -pedantic ex_07_challenge.c -o ex_07_challenge
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define BUFSZ 256

typedef struct {
    char   *data;
    size_t  len;
} String_Slice;

/* --- Helper functions (already implemented) --- */

String_Slice slice_from_cstring(char *cstring) {
    return (String_Slice){
        .data = cstring,
        .len  = strlen(cstring),
    };
}

String_Slice slice_from_range(char *data, size_t len) {
    return (String_Slice){ .data = data, .len = len };
}

int slice_eq(String_Slice a, String_Slice b) {
    if (a.len != b.len) return 0;
    for (size_t i = 0; i < a.len; ++i) {
        if (a.data[i] != b.data[i]) return 0;
    }
    return 1;
}

int slice_starts_with(String_Slice s, String_Slice prefix) {
    if (prefix.len > s.len) return 0;
    for (size_t i = 0; i < prefix.len; ++i) {
        if (s.data[i] != prefix.data[i]) return 0;
    }
    return 1;
}

String_Slice slice_take(String_Slice s, size_t n) {
    if (n > s.len) n = s.len;
    return (String_Slice){ s.data, n };
}

String_Slice slice_drop(String_Slice s, size_t n) {
    if (n > s.len) n = s.len;
    return (String_Slice){ s.data + n, s.len - n };
}

void print_slice(String_Slice s) {
    for (size_t i = 0; i < s.len; ++i) {
        putchar(s.data[i]);
    }
}

/* ---------------------------------------------------------------- */
/* --- YOUR TASK: Implement the helper functions below --- */

/* Returns 1 if c is a whitespace character (space or tab), 0 otherwise. */
int is_field_sep(char c) {
    /*@*/
    return /*@*/;
}

/* Advance s past any leading whitespace.
 * Return the first non-whitespace position (or empty if fully whitespace). */
String_Slice trim_left(String_Slice s) {
    /*@*/
    return /*@*/;
}

/* Extract the next field from the beginning of s.
 * A field runs until whitespace or end of slice.
 * Return the field as a slice (without trailing whitespace).
 * HINT: use trim_left first, then slice_take up to the first separator. */
String_Slice next_field(String_Slice *s) {
    /* Trim leading whitespace first */
    *s = trim_left(*s);
    if (s->len == 0) {
        return (String_Slice){ NULL, 0 };
    }

    /*@*/
    /* Find where the field ends (first whitespace char) */
    size_t field_len = 0;
    /*@*/
    /* walk forward until whitespace or end */

    /* Extract the field */
    /*@*/
    String_Slice field = slice_take(/*@*/);

    /* Advance s past the field and its trailing separator */
    /*@*/
    *s = slice_drop(/*@*/);

    return field;
}

/* ---------------------------------------------------------------- */

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
        String_Slice line = slice_from_cstring(lines[i]);

        /* Skip blank lines */
        line = trim_left(line);
        if (line.len == 0) {
            printf("[SKIP] Blank line\n");
            continue;
        }

        /* Skip comments */
        String_Slice comment_prefix = slice_from_cstring("#");
        if (slice_starts_with(line, comment_prefix)) {
            printf("[SKIP] Comment: ");
            print_slice(line);
            putchar('\n');
            continue;
        }

        /* Parse the 6 fields */
        printf("[LINE] ");
        print_slice(line);
        putchar('\n');

        char device[64], mount[64], fstype[64], options[64];
        char dump_str[8], pass_str[8];

        /* Extract each field using next_field */
        String_Slice f_device   = next_field(&line);
        String_Slice f_mount    = next_field(&line);
        String_Slice f_fstype   = next_field(&line);
        String_Slice f_options  = next_field(&line);
        String_Slice f_dump     = next_field(&line);
        String_Slice f_pass     = next_field(&line);

        /* Build output using snprintf (safe way!) */
        snprintf(device, sizeof(device), "%.*s", (int)f_device.len,  f_device.data);
        snprintf(mount,  sizeof(mount),  "%.*s", (int)f_mount.len,   f_mount.data);
        snprintf(fstype, sizeof(fstype), "%.*s", (int)f_fstype.len,  f_fstype.data);
        snprintf(options,sizeof(options),"%.*s", (int)f_options.len, f_options.data);
        snprintf(dump_str, sizeof(dump_str), "%.*s", (int)f_dump.len, f_dump.data);

        /* For the last field (pass), check if it exists */
        if (f_pass.data != NULL) {
            snprintf(pass_str, sizeof(pass_str), "%.*s", (int)f_pass.len, f_pass.data);
        } else {
            snprintf(pass_str, sizeof(pass_str), "?");
        }

        char output[512];
        snprintf(output, sizeof(output),
                 "  device=%s  mount=%s  type=%s  opts=%s  dump=%s  pass=%s",
                 device, mount, fstype, options, dump_str, pass_str);
        printf("%s\n", output);
    }

    printf("\n--- Challenge complete! ---\n");
    printf("All parsing used zero-copy String_Slice operations.\n");
    printf("No strtok, no strcpy, no strcmp, no malloc in the parser.\n");

    return 0;
}
