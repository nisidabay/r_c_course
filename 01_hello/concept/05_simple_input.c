#include <stdio.h>

int main(void)
{
    char name[32];
    char input[32];
    int age;

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);

    printf("Enter your age: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &age);

    printf("Hello, %s! You are %d years old.\n", name, age);

    return 0;
}

// Thinking in C:
// C has no built-in input mechanism — fgets reads raw text from stdin.
// sscanf parses a string into typed variables, returning how many items matched.
// Unlike Python's input() or JavaScript's prompt(), C input requires explicit buffers.
// The & operator gives sscanf the address of a variable so it can modify it.
// Always check fgets return value to handle end-of-file gracefully.
