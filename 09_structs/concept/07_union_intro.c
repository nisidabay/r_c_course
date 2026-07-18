/*
 * 07_union_intro.c — union: overlapping memory for different types
 * Group 09 — Structs
 *
 * A union is like a struct, BUT all members share THE SAME memory
 * location.  The size of a union is the size of its LARGEST member.
 *
 *   union number {
 *       int   i;
 *       float f;
 *   };
 *
 * sizeof(union number) == sizeof(float)  (4 bytes, the larger member)
 *
 * You can store an int OR a float in the same space — but NOT both
 * at the same time.  Writing to one member overwrites the others.
 *
 * Unions are useful for:
 *   - Variant types (a value that can be one of several types)
 *   - Type-punning (inspecting the raw bytes of a float as an int)
 *   - Saving memory when only one of several fields is used at a time
 *   - Parsing binary protocols (overlay a struct onto a byte buffer)
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * A tagged union — the most common safe pattern.
 * The "tag" (an enum) tracks which member is currently active.
 */
enum type_tag { TAG_INT, TAG_FLOAT, TAG_STRING };

union value {
    int    i;
    float  f;
    char  *s;
};

struct tagged_value {
    enum type_tag tag;
    union value   val;
};

static void print_value(struct tagged_value *tv)
{
    switch (tv->tag) {
    case TAG_INT:
        printf("  int:    %d\n", tv->val.i);
        break;
    case TAG_FLOAT:
        printf("  float:  %.2f\n", tv->val.f);
        break;
    case TAG_STRING:
        printf("  string: %s\n", tv->val.s);
        break;
    }
}

/*
 * Type-punning: inspecting the raw bytes of a float through an int.
 * This is a classic (though technically implementation-defined) use
 * of unions to understand floating-point representation.
 */
union float_bits {
    float f;
    unsigned int bits;
};

static void print_float_bits(float f)
{
    union float_bits fb = { .f = f };
    printf("  %f  as hex: 0x%08X\n", f, fb.bits);
}

int main(void)
{
    printf("=== union — Overlapping Memory ===\n\n");

    /* ---- Basic union layout ---- */
    printf("Sizeof union {int, float, char *}: %zu bytes\n",
           sizeof(union value));
    printf("(Compare: sizeof(int) = %zu, sizeof(float) = %zu, "
           "sizeof(char *) = %zu)\n\n",
           sizeof(int), sizeof(float), sizeof(char *));

    /* ---- Tagged union (safe pattern) ---- */
    printf("--- Tagged union ---\n");

    struct tagged_value tv;

    tv.tag = TAG_INT;
    tv.val.i = 42;
    print_value(&tv);

    tv.tag = TAG_FLOAT;
    tv.val.f = 3.14f;
    print_value(&tv);

    tv.tag = TAG_STRING;
    tv.val.s = "hello, union";
    print_value(&tv);

    /* ---- Type-punning ---- */
    printf("\n--- Type-punning: float bits as hex ---\n");
    print_float_bits(1.0f);
    print_float_bits(3.14f);
    print_float_bits(0.0f);

    printf("\n(Note: 1.0f in IEEE 754 single precision is 0x3F800000.)\n");

    return EXIT_SUCCESS;
}

// Thinking in C:
// struct  = "I need ALL of these at the same time"
// union   = "I need ONE of these at a time"
//
// The tagged union pattern (enum tag + union value) is the C way of
// implementing sum types / variant types.  It's what compilers like
// GCC use internally for their AST nodes, and what real protocol
// parsers use for packet headers.
//
// Without the tag, unions are dangerous: reading the wrong member
// is undefined behavior (technically: the read value is trap-representation
// dependent).  Always pair a union with an enum or other discriminator.
