/*
 * How do I control symbol visibility with static and extern?
 *
 * - static: limits visibility to the current translation unit (file scope).
 * - extern: declares a symbol defined in another translation unit.
 *
 * This file demonstrates both, with a static helper (file-local)
 * and an extern function (visible to other .c files).
 */

#include <stdio.h>
#include <stdlib.h>

/* ---- static (file-local) helpers ---- */

static int double_value(int x)
{
    return x * 2;
}

static const char *get_tag(void)
{
    return "[static-extern-demo]";
}

/* ---- extern-visible function ---- */
/* This could be called from another .c file after a declaration:
 *   extern int compute_result(int a, int b); */

extern int compute_result(int a, int b)
{
    int doubled = double_value(a);
    int sum     = doubled + b;
    return sum;
}

int main(void)
{
    int result = compute_result(5, 3);
    printf("%s compute_result(5, 3) = %d\n", get_tag(), result);

    /* double_value is NOT accessible outside this file */
    printf("%s Internal double: %d\n", get_tag(), double_value(7));

    return EXIT_SUCCESS;
}

/* Thinking in C: static hides symbols from the linker; extern promises
 * they exist elsewhere. Use static by default for helpers, extern only
 * for the public API exposed across translation units. */


// 💡 Thinking in C:
// static makes a function private to its file. extern makes it visible across files.
