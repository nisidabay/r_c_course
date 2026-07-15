#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Age calculator program — predicts future age given current age and years

    /*
     * Declare current age and years to add,
     * compute the future age,
     * then print the result.
     */

    int age = 15;
    int years = 7;

    int future_age = age + years;  // add years to current age

    printf("In %d years you will be %d.\n", years, future_age);

    return EXIT_SUCCESS;
}
