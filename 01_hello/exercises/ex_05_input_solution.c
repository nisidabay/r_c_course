#include <stdio.h>
#include <string.h>

/* consume_remaining: discard any leftover characters in stdin if the
 * buffer was too small to hold the full input line.
 */
static void consume_remaining(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main(void)
{
    /* buffer for user's name — large enough for typical names */
    char name[32];
    /* buffer for favorite number string — 12 = 10 digits + possible '-' + newline + null */
    char favorite_str[12];
    int fav;

    printf("Enter your name: ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    /* If the input was longer than 31 chars, flush the rest from stdin */
    size_t len = strlen(name);
    if (len > 0 && name[len - 1] != '\n')
        consume_remaining();
    /* Strip trailing newline so the output fits on one line */
    name[strcspn(name, "\n")] = '\0';

    printf("Enter your favorite number: ");
    if (fgets(favorite_str, sizeof(favorite_str), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    len = strlen(favorite_str);
    if (len > 0 && favorite_str[len - 1] != '\n')
        consume_remaining();

    /*
     * sscanf returns how many items it matched. Always check!
     * Here it parses the favorite_str buffer as an integer.
     * Later (Group 03+) you'll use strtol for full error detection
     * (pointers from Group 06 make it click).
     */
    if (sscanf(favorite_str, "%d", &fav) != 1) {
        printf("Invalid input: expected a number.\n");
        return 1;
    }

    printf("Hello, %s! Your favorite number is %d.\n", name, fav);

    return 0;
}
