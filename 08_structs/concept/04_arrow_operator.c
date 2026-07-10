/*
 * 04_arrow_operator.c — -> when you have a POINTER to a struct
 *
 * ptr->member  is exactly equivalent to  (*ptr).member
 * The arrow is just syntactic sugar — it dereferences AND accesses in one
 * step. Students MUST see both forms.
 */

#include <stdio.h>

typedef struct {
    char title[64];
    int  pages;
} Book;

int main(void) {
    Book hp = {"Harry Potter", 309};
    Book *ptr = &hp;       /* pointer to struct */

    /* --- Both forms are equivalent --- */

    /* Arrow form (preferred) */
    printf("Arrow:     %s has %d pages\n", ptr->title, ptr->pages);

    /* Dereference-then-dot form (equivalent) */
    printf("Deref+dot: %s has %d pages\n", (*ptr).title, (*ptr).pages);

    /* Modify through pointer — using arrow */
    ptr->pages = 312;
    printf("Updated pages via arrow: %d\n", ptr->pages);

    /* Modify through pointer — using deref+dot */
    (*ptr).pages = 320;
    printf("Updated pages via (*ptr): %d\n", (*ptr).pages);

    return 0;
}
/*
 * Thinking in C:
 *   — ptr->field  ≡  (*ptr).field  — never forget this equivalence.
 *   — Arrow is preferred because it's one operator instead of two.
 *   — The parentheses in (*ptr).field are REQUIRED; '.' has higher
 *     precedence than '*'. (Without parens: *(ptr.field) — wrong.)
 */
