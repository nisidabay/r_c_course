/* How do I work with string slices in C? */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t len;
} String_Slice;

static String_Slice slice_from_cstr(const char *s) {
    String_Slice sl = {s, strlen(s)};
    return sl;
}

static void slice_print(String_Slice sl) {
    for (size_t i = 0; i < sl.len; i++)
        putchar(sl.data[i]);
}

static int slice_compare(String_Slice a, String_Slice b) {
    if (a.len != b.len)
        return a.len < b.len ? -1 : 1;
    return memcmp(a.data, b.data, a.len);
}

static String_Slice slice_sub(String_Slice sl, size_t start, size_t length) {
    if (start >= sl.len)
        return (String_Slice){NULL, 0};
    if (start + length > sl.len)
        length = sl.len - start;
    return (String_Slice){sl.data + start, length};
}

int main(void) {
    String_Slice msg = slice_from_cstr("Hello, string slices!");

    printf("Full slice: ");
    slice_print(msg);
    putchar('\n');

    String_Slice sub = slice_sub(msg, 7, 6);
    printf("Substring:  ");
    slice_print(sub);
    putchar('\n');

    String_Slice a = slice_from_cstr("apple");
    String_Slice b = slice_from_cstr("banana");
    int cmp = slice_compare(a, b);
    printf("Compare: %s\n", cmp < 0 ? "apple < banana" :
                               cmp > 0 ? "apple > banana" : "equal");

    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// String_Slice is a pointer plus a length. No backslash-zero needed. No hidden strlen calls. Zero-copy by design.
