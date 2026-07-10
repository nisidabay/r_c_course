/*
 * array_reverse.c
 *
 * Reads 10 integers from stdin, stores them in an array,
 * reverses the array in-place using pointer arithmetic,
 * then prints both the original and reversed arrays.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic array_reverse.c -o array_reverse
 *
 * Concepts: pointers, pointer arithmetic, fgets + sscanf, no array subscripts
 */

#include <stdio.h>
#include <string.h>  /* for strlen */
#include <stdlib.h>  /* for EXIT_SUCCESS */

#define ARRAY_SIZE 10
#define LINE_SIZE 64

/*
 * reverse: reverses an int array in-place using two pointers.
 * Parameters:
 *   arr  - pointer to the first element of the array
 *   len  - number of elements in the array
 *
 * No array subscript notation is used — only pointer dereference.
 */
void reverse(int *arr, size_t len)
{
    int *start = arr;           /* pointer to first element */
    int *end   = arr + len - 1; /* pointer to last  element */

    while (start < end)
    {
        /* swap *start and *end via a temporary */
        int temp = *start;
        *start   = *end;
        *end     = temp;

        /* walk pointers toward each other */
        start++;
        end--;
    }
}

/*
 * print_array: prints an int array to stdout, one element per line
 * with a label.  Also uses pointer notation.
 */
void print_array(const int *arr, size_t len, const char *label)
{
    size_t i;

    printf("%s:\n", label);
    for (i = 0; i < len; i++)
    {
        /* access via pointer arithmetic, not subscript */
        printf("  %d\n", *(arr + i));
    }
    putchar('\n');
}

int main(void)
{
    char  line[LINE_SIZE];
    int   nums[ARRAY_SIZE];
    size_t count = 0;

    printf("Enter %d integers, one per line:\n", ARRAY_SIZE);

    while (count < ARRAY_SIZE)
    {
        int   val;
        int   parsed;
        size_t len;

        /* read a line */
        if (fgets(line, sizeof line, stdin) == NULL)
        {
            break;  /* EOF or read error */
        }

        /* strip trailing newline (for cleaner display) */
        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        /* parse an integer from the line */
        parsed = sscanf(line, "%d", &val);
        if (parsed == 1)
        {
            nums[count] = val;
            count++;
        }
        else
        {
            printf("Invalid input, please enter an integer.\n");
        }
    }

    /* print original order */
    print_array(nums, ARRAY_SIZE, "Original");

    /* reverse in-place */
    reverse(nums, ARRAY_SIZE);

    /* print reversed order */
    print_array(nums, ARRAY_SIZE, "Reversed");

    return EXIT_SUCCESS;
}
