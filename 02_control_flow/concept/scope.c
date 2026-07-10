/*
 * How do scope and visibility work in C?
 *
 * Scope determines where a name is visible.  Block scope
 * (inside { }) is local; file scope is visible to the whole
 * translation unit.  static limits linkage to the current
 * file.
 */

#include <stdio.h>
#include <stdlib.h>

/* File-scope variable -- visible to all functions in this file */
static int file_scope_counter = 0;

/* File-scope constant -- implicitly static when const */
static const int MAX_VALUE = 100;

static void demo_block_scope(void) {
    /* This variable exists only inside this function */
    int local = 10;
    printf("  demo_block_scope: local = %d\n", local);

    {
        /* Inner block -- shadows outer 'local' */
        int local = 99;
        printf("  Inner block:     local = %d (shadows outer)\n", local);
    }

    /* Back to the original local */
    printf("  After inner block: local = %d\n", local);
}

static void use_file_scope(void) {
    ++file_scope_counter;
    printf("  use_file_scope: counter = %d (max %d)\n",
           file_scope_counter, MAX_VALUE);
}

int main(void) {
    printf("=== Block scope ===\n");
    demo_block_scope();

    printf("\n=== File scope ===\n");
    use_file_scope();
    use_file_scope();
    use_file_scope();

    printf("\nfile_scope_counter = %d after three calls\n",
           file_scope_counter);

    return EXIT_SUCCESS;
}

/*
 * ============================================================
 * Thinking in C
 * --------------------------
 * C has four kinds of scope: block (inside { }), function
 * (goto labels), file (outside any function), and function
 * prototype (parameter names in declarations).  Prefer block
 * scope: keep variables as local as possible.  File-scope
 * variables create hidden coupling between functions.
 * Use static on file-scope variables to prevent external
 * linkage and keep your module self-contained.
 * ============================================================
 */


// 💡 Thinking in C:
// Variables live inside their {} block. A variable declared inside if dies at }.
