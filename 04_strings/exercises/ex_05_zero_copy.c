/*
 * Exercise 05: The magic of zero-copy slicing (THE CROWN JEWEL)
 *
 * Concept: slice_take and slice_drop create new slices by ADJUSTING
 *          the data pointer and length. NO malloc, NO memcpy,
 *          NO character copying. Just pointer arithmetic. This is
 *          the power of the data+len pattern — slicing without allocating.
 *
 * YOUR TASK: Implement slice_take and slice_drop.
 *
 *   slice_take(s, n): return the first n bytes of slice s.
 *     - Clamp n to s.len if n exceeds the slice length.
 *     - NO data is copied — just shrink .len.
 *
 *   slice_drop(s, n): skip the first n bytes of slice s.
 *     - If n exceeds s.len, result is empty (len=0).
 *     - NO data is copied — just advance .data forward by n.
 *
 * Once you implement both, the main() function will test them.
 *
 * Note: Exercises 03+ use size_t (from <stddef.h>).
 *
 * Safe C Standard: no strcpy/strcat/sprintf/scanf/atoi/atof.
 * Compile with: gcc -std=c11 -Wall -Wextra -pedantic ex_05_zero_copy.c -o ex_05_zero_copy
 */

#include <stddef.h>   // size_t is an unsigned integer type from <stddef.h>, used for sizes and indices
#include <stdio.h>
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

/* --- YOUR TASK: Implement slice_take ---
 *
 * Return the first n characters of slice s.
 * If n > s.len, return the entire slice (clamp n to s.len).
 * Do NOT copy any data — only adjust the struct fields.
 */
String_Slice slice_take(String_Slice s, size_t n) {
    /*@*/
    return (String_Slice){ /*@*/ };
}

/* --- YOUR TASK: Implement slice_drop ---
 *
 * Skip the first n characters of slice s.
 * If n > s.len, return an empty slice (len = 0).
 * Do NOT copy any data — advance .data and shrink .len.
 */
String_Slice slice_drop(String_Slice s, size_t n) {
    /*@*/
    return (String_Slice){ /*@*/ };
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

    return 0;
}
