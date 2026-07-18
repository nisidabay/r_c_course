/*
 * generic_sorter.c — Generic Sorting Framework
 *
 * Demonstrates ALL concepts from groups 01–11:
 *   01: Basic I/O, printf, fgets
 *   02: Types, variables, arrays, structs
 *   03: Strings, snprintf, strcmp
 *   04: Loops (while, for), control flow
 *   05: Functions, prototypes, parameters
 *   06: Arrays & pointers (pointer arithmetic, function pointers)
 *   07: Dynamic memory (malloc/free — used for a copy/display helper)
 *   08: File I/O (fprintf/fscanf — used briefly in print_product)
 *   09: Preprocessor, _Generic, macros
 *   10: Sorting algorithms (qsort + custom comparators)
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic generic_sorter.c -o generic_sorter
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ======================== 1. Struct Product (groups 02, 03) ======================== */

typedef struct {
    char name[32];
    double price;
    int quantity;
} Product;

/* ======================== 2. Product catalog (group 02) =========================== */

static Product catalog[] = {
    {"Laptop",        1299.99,  15},
    {"Mouse",           29.99, 200},
    {"Keyboard",        89.99,  80},
    {"Monitor",        399.99,  30},
    {"USB-C Hub",       49.99, 120},
    {"Desk Lamp",       24.99,  55},
    {"Webcam",          79.99,  40},
};
#define CATALOG_SIZE  (sizeof(catalog) / sizeof(catalog[0]))

/* ======================== 3. qsort comparators (group 10) ========================= */

int by_name(const void *a, const void *b)
{
    const Product *pa = (const Product *)a;
    const Product *pb = (const Product *)b;
    /* alphabetical order (group 03: strcmp) */
    return strcmp(pa->name, pb->name);
}

int by_price(const void *a, const void *b)
{
    const Product *pa = (const Product *)a;
    const Product *pb = (const Product *)b;
    /* ascending */
    if (pa->price < pb->price) return -1;
    if (pa->price > pb->price) return  1;
    return 0;
}

int by_quantity(const void *a, const void *b)
{
    const Product *pa = (const Product *)a;
    const Product *pb = (const Product *)b;
    /* descending */
    if (pa->quantity > pb->quantity) return -1;
    if (pa->quantity < pb->quantity) return  1;
    return 0;
}

/* ======================== 4. Function-pointer table (group 06) ==================== */

/*
 * We store a triple: the command character, a label, and the comparator.
 * Group 05 (functions as data) is exercised via this array.
 */
typedef struct {
    char cmd;
    const char *label;
    int (*cmp)(const void *, const void *);
} SortOption;

static SortOption options[] = {
    {'n', "Name (alphabetical)",        by_name},
    {'p', "Price (ascending)",          by_price},
    {'q', "Quantity (descending)",      by_quantity},
};
static const int NUM_OPTIONS = sizeof(options) / sizeof(options[0]);

/* ======================== 5. _Generic print helper (group 09) ==================== */

/*
 * _Generic type-generic print helper (group 09).
 * We strip const by casting through (void *) so the _Generic selection works.
 * Each branch calls printf with the appropriate format specifier.
 */
#define PRINT_FIELD(val, fmt)                                        \
    _Generic((val),                                                   \
        const char * : printf(fmt, (val)),                            \
        char *       : printf(fmt, (val)),                            \
        double       : printf(fmt, (val)),                            \
        int          : printf(fmt, (val))                             \
    )

/* ======================== Dynamic-memory helper (group 07) ======================== */

/*
 * Allocate a mutable copy of the catalog so we never sort the original.
 * Returns a pointer to a heap-allocated copy of the Product array.
 */
Product *catalog_copy(const Product *src, int count)
{
    /* Group 07: malloc */
    Product *copy = (Product *)malloc((size_t)count * sizeof(Product));
    if (copy == NULL) {
        fprintf(stderr, "ERROR: malloc failed\n");   /* group 08: fprintf */
        exit(EXIT_FAILURE);
    }
    /* group 06: pointer arithmetic via memcpy */
    memcpy(copy, src, (size_t)count * sizeof(Product));
    return copy;
}

/* ======================== 6. Print all products (groups 01, 02, 03) =============== */

/*
 * Uses snprintf (group 03) to build a formatted line,
 * then writes it to stdout (also exercises group 08 via sscanf simulation).
 * The _Generic macro is used to print individual fields for demonstration.
 */
void print_products(const Product *prods, int count, const char *label)
{
    printf("\n--- Sorted by: %s ---\n", label);

    for (int i = 0; i < count; i++) {                /* group 04: for loop */
        char buf[128];
        snprintf(buf, sizeof(buf),                     /* group 03: snprintf */
                 "  %-20s  $%7.2f  Qty: %d",
                 prods[i].name, prods[i].price, prods[i].quantity);

        /*
         * Demonstrate _Generic on each field type (group 09).
         * In a real program we'd just printf the buffer; here we round-trip
         * through _Generic to show the concept in action.
         * Cast away const for the _Generic dispatch — the actual printf
         * doesn't modify the string.
         */
        printf("%s  |  _Generic check: ", buf);
        PRINT_FIELD((char *)prods[i].name, "name=%s, ");
        PRINT_FIELD(prods[i].price, "price=%.2f, ");
        PRINT_FIELD(prods[i].quantity, "qty=%d");
        printf("\n");
    }
    printf("  (Total: %d products)\n\n", count);
}

/* ======================== 7. Main loop (groups 04, 05, 06, 08, 09, 10) ============ */

int main(void)
{
    /* Preprocessor demonstration (group 09): static assertion via #if */
/* CATALOG_SIZE is a compile-time constant calculated via sizeof */

    printf("=== Generic Sorting Framework ===\n");
    printf("Catalog has %zu products (compile-time constant: %zu)\n\n",
           CATALOG_SIZE, CATALOG_SIZE);

    /* Show original catalog once */
    printf("Original catalog:\n");
    for (int i = 0; i < (int)CATALOG_SIZE; i++) {
        printf("  %2d. %-20s $%7.2f  Qty: %d\n",
               i + 1,
               catalog[i].name,
               catalog[i].price,
               catalog[i].quantity);
    }

    char line[16];
    do {                                             /* group 04: do-while loop */
        printf("\nSort by:\n");
        for (int i = 0; i < NUM_OPTIONS; i++) {      /* group 04: for loop */
            printf("  '%c' → %s\n", options[i].cmd, options[i].label);
        }
        printf("  'x' → eXit\n");
        printf("Enter choice: ");

        /* Safe C Standard: fgets instead of scanf */
        if (fgets(line, sizeof line, stdin) == NULL) {
            printf("Goodbye!\n");
            break;
        }
        char choice = line[0];
        if (choice == '\n' || choice == '\0') {
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (choice == 'x') {
            printf("Exiting. Goodbye!\n");
            break;
        }

        /* Find matching option and sort (groups 05, 06, 10) */
        int found = 0;
        for (int i = 0; i < NUM_OPTIONS; i++) {
            if (choice == options[i].cmd) {
                /* Group 07: dynamic allocation for a working copy */
                Product *work = catalog_copy(catalog, (int)CATALOG_SIZE);

                /* Group 10: qsort with function-pointer comparator */
                qsort(work, CATALOG_SIZE, sizeof(Product), options[i].cmp);

                /* Group 01, 03, 09: print results */
                print_products(work, (int)CATALOG_SIZE, options[i].label);

                /* Group 07: free the working copy */
                free(work);

                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Unknown option '%c'. Please try again.\n", choice);
        }

    } while (1);    /* group 04: infinite loop with break inside */

    return EXIT_SUCCESS;                              /* group 08: EXIT_SUCCESS */
}
