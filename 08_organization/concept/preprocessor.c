/*
 * How do I use the C preprocessor?
 *
 * The preprocessor runs before compilation: #define, #ifdef/#ifndef,
 * #if/#elif/#else, #include, and special macros like __LINE__,
 * __FILE__, __func__, and stringification (#).
 */

#include <stdio.h>
#include <stdlib.h>

/* ---- macros ---- */

#define VERSION_MAJOR 1
#define VERSION_MINOR 0

/* Stringification: # converts a macro parameter to a string literal */
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

/* Token pasting: ## concatenates tokens into a single identifier */
#define MAKE_VERSION_IMPL(maj, min) maj ## _ ## min
#define MAKE_VERSION_STR(maj, min) TO_STRING(MAKE_VERSION_IMPL(maj, min))

/* Conditional compilation */
#ifdef NDEBUG
    #define ASSERT_MSG(cond, msg) ((void)0)
#else
    #define ASSERT_MSG(cond, msg)                                         \
        do {                                                               \
            if (!(cond)) {                                                 \
                fprintf(stderr, "%s:%d: %s -- Assertion failed: %s\n",     \
                        __FILE__, __LINE__, __func__, (msg));              \
                exit(EXIT_FAILURE);                                        \
            }                                                              \
        } while (0)
#endif

int main(void)
{
    printf("File:       %s\n", __FILE__);
    printf("Line:       %d\n", __LINE__);
    printf("Date:       %s %s\n", __DATE__, __TIME__);
    printf("Version:    %s\n", MAKE_VERSION_STR(VERSION_MAJOR, VERSION_MINOR));

    /* Stringification demo */
    printf("VERSION_MAJOR stringified: %s\n", STRINGIFY(VERSION_MAJOR));

    /* Conditional compilation demo */
    ASSERT_MSG(1 == 1, "truth is truth");

#ifndef NDEBUG
    printf("Debug build: assertions are active.\n");
#endif

    return EXIT_SUCCESS;
}

/* Thinking in C: The preprocessor is a text-replacement engine.
 * Use macros for constants, conditional compilation for debug/release,
 * and stringification for diagnostic messages. Avoid function-like macros
 * when a real function works. */


// 💡 Thinking in C:
// Hash-define creates macros. Hash-ifdef enables conditional compilation. The preprocessor runs before the compiler.
