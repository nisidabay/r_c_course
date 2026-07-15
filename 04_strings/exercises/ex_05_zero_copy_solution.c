/*
 * Exercise 05: The magic of zero-copy slicing (THE CROWN JEWEL) — SOLUTION
 *
 * Concept: slice_take and slice_drop create new slices by ADJUSTING
 *          the data pointer and length. NO malloc, NO memcpy,
 *          NO character copying. Just pointer arithmetic. This is
 *          the power of the data+len pattern — slicing without allocating.
 *
 * Note: Exercises 03+ use size_t (from <stddef.h>).
 *
 * Compile with: gcc -std=c11 -Wall -Wextra -pedantic ex_05_zero_copy.c -o ex_05_zero_copy
 */

#include <stddef.h>   // size_t is an unsigned integer type from <stddef.h>, used for sizes and indices
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char   *data;
    size_t  len;
} String_Slice;

String_Slice slice_from_cstring(char *cstring) {
    return (String_Slice){
        .data = cstring,
        .len  = strlen(cstring),
    };
}

void print_slice(String_Slice s) {
    for (size_t i = 0; i < s.len; ++i) {
        putchar(s.data[i]);
    }
}

/* slice_take: return first n bytes by CLAMPING .len.
 * If n exceeds slice length, take everything.
 * NO data is copied — we just shrink .len. */
String_Slice slice_take(String_Slice s, size_t n) {
    if (n > s.len) n = s.len;
    return (String_Slice){ s.data, n };
}

/* slice_drop: skip first n bytes by ADVANCING .data.
 * If n exceeds slice length, result is empty (data points past end, len=0).
 * NO data is copied — we just move the pointer forward. */
String_Slice slice_drop(String_Slice s, size_t n) {
    if (n > s.len) n = s.len;
    return (String_Slice){ s.data + n, s.len - n };
}

int main(void) {
    char *text = "hello world";
    String_Slice full = slice_from_cstring(text);

    printf("Original:  \"");
    print_slice(full);
    printf("\"  (data = %p, len = %zu)\n\n", (void *)full.data, full.len);

    /* --- slice_take: first N characters, zero copy --- */
    String_Slice first5 = slice_take(full, 5);
    printf("slice_take(full, 5):  \"");
    print_slice(first5);
    printf("\"  (data = %p, len = %zu)  <- SAME data pointer\n",
           (void *)first5.data, first5.len);

    /* --- slice_drop: skip first N characters, zero copy --- */
    String_Slice after6 = slice_drop(full, 6);
    printf("slice_drop(full, 6):  \"");
    print_slice(after6);
    printf("\"  (data = %p, len = %zu)  <- data pointer ADVANCED by 6\n",
           (void *)after6.data, after6.len);

    /* --- Take then drop: extract substring in the middle --- */
    String_Slice middle = slice_take(slice_drop(full, 6), 5);
    printf("slice_take(slice_drop(full, 6), 5):  \"");
    print_slice(middle);
    printf("\"  (data = %p, len = %zu)\n", (void *)middle.data, middle.len);

    /* Proof: ALL slices point into the original buffer, nowhere else */
    printf("\n*** VERIFICATION: All slices point into the original buffer ***\n");
    printf("Original data: %p\n", (void *)full.data);
    printf("First5  data: %p  (offset %td bytes)\n",  (void *)first5.data,  first5.data  - full.data);
    printf("After6  data: %p  (offset %td bytes)\n",  (void *)after6.data,  after6.data  - full.data);
    printf("Middle  data: %p  (offset %td bytes)\n",  (void *)middle.data,  middle.data  - full.data);

    printf("\nZERO bytes were copied. ZERO allocations. Just pointer math.\n");
    printf("This is impossible with null-terminated strings. This is the magic.\n");

    return EXIT_SUCCESS;
}
