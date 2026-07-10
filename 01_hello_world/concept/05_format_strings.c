/* How do I format output with printf? */

#include <stdio.h>

int main(void) {
    const char *name = "Alice";
    int age = 30;
    double height = 1.68;

    printf("Name: %s\n", name);
    printf("Age:  %d\n", age);
    printf("Ht:   %.2f m\n", height);
    printf("Hex:  0x%x\n", age);

    return 0;
}
