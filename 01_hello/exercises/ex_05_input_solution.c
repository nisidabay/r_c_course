#include <stdio.h>

int main(void)
{
    char name[32];
    char input[32];
    int fav;

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);

    printf("Enter your favorite number: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &fav);

    printf("Hello, %s! Your favorite number is %d.\n", name, fav);

    return 0;
}
