#include <stdio.h>
#include <string.h>

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
    /* Strip trailing newline so the output fits on one line */
    name[strcspn(name, "\n")] = '\0';

    printf("Enter your favorite number: ");
    if (fgets(favorite_str, sizeof(favorite_str), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

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
