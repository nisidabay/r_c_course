#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/*  String_Slice — a zero-copy string view                             */
/* ------------------------------------------------------------------ */

typedef struct {
    char  *data;
    size_t len;
} String_Slice;

/* Print a String_Slice character by character */
void print_slice(String_Slice s) {
    for (size_t i = 0; i < s.len; ++i)
        putchar(s.data[i]);
}

/* Build a String_Slice from a null-terminated C string */
String_Slice slice_from_cstring(char *cstring) {
    return (String_Slice){
        .data = cstring,
        .len  = strlen(cstring),
    };
}

/* Take the first n characters (or less if slice is shorter) */
String_Slice slice_take(String_Slice s, size_t n) {
    if (n > s.len) n = s.len;
    return (String_Slice){ s.data, n };
}

/* Drop the first n characters (or all if slice is shorter) */
String_Slice slice_drop(String_Slice s, size_t n) {
    if (n > s.len) n = s.len;
    return (String_Slice){ s.data + n, s.len - n };
}

/* Check if a slice starts with a given prefix */
int slice_starts_with(String_Slice s, String_Slice prefix) {
    if (prefix.len > s.len) return 0;
    for (size_t i = 0; i < prefix.len; ++i)
        if (s.data[i] != prefix.data[i])
            return 0;
    return 1;
}

/* Trim leading and trailing whitespace */
String_Slice slice_trim(String_Slice s) {
    while (s.len > 0 && isspace((unsigned char)s.data[0]))
        s = slice_drop(s, 1);
    while (s.len > 0 && isspace((unsigned char)s.data[s.len - 1]))
        s = slice_take(s, s.len - 1);
    return s;
}

/* Split on delimiter (mutating the input slice).
   Returns the portion before delimiter, advances *s past it. */
String_Slice slice_split(String_Slice *s, char delimiter) {
    size_t i = 0;
    while (i < s->len && s->data[i] != delimiter)
        ++i;
    String_Slice result = slice_take(*s, i);
    if (i < s->len)
        *s = slice_drop(*s, i + 1);
    else
        *s = slice_drop(*s, i);
    return result;
}

/* ------------------------------------------------------------------ */
/*  Fstab parser                                                       */
/* ------------------------------------------------------------------ */

int main(void) {
    FILE *f = fopen("/etc/fstab", "r");
    if (!f) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    static const char *field_names[] = {
        "device", "mount", "type", "options", "dump", "pass"
    };

    char   buf[512];

    while (fgets(buf, sizeof buf, f)) {
        String_Slice line = slice_trim(slice_from_cstring(buf));
        if (line.len == 0) continue;                         /* empty */
        if (slice_starts_with(line, slice_from_cstring("#"))) continue; /* comment */

        /* Print a divider before each entry */
        puts("---");

        size_t idx = 0;
        while (line.len > 0 && idx < 6) {
            /* Skip any leading whitespace (spaces AND tabs) */
            while (line.len > 0 && isspace((unsigned char)line.data[0]))
                line = slice_drop(line, 1);

            if (line.len == 0) break;

            /* Extract field up to next space or tab */
            String_Slice field;
            {
                size_t i = 0;
                while (i < line.len && line.data[i] != ' '
                       && line.data[i] != '\t')
                    ++i;
                field = slice_take(line, i);
                line  = slice_drop(line, i);
            }

            if (field.len == 0) continue;

            printf("%-7s : ", field_names[idx]);
            print_slice(field);
            putchar('\n');
            ++idx;
        }
    }

    fclose(f);
    return EXIT_SUCCESS;
}
