
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>



typedef struct numbers_t
{
    int n;
    int* data;
} numbers_t;


int is_even(int element)
{
    return(element % 2 == 0);
}

void variation_elements(numbers_t* numbers)
{
    for(int idx = 0; idx < numbers->n; ++idx)
    {
        if(is_even(numbers->data[idx]))
        {
            numbers->data[idx] *= 2;
            printf("element of %d cell: %d\n", idx, numbers->data[idx]);
        }
        else
        {
            numbers->data[idx] += 2;
            printf("element of %d cell: %d\n", idx, numbers->data[idx]);
        }
    }
}

void input_dates(numbers_t* numbers)
{
    printf("Input numbers of elements of array.\n");
    scanf("%d", &numbers->n);

    numbers->data = (int*) calloc(numbers->n, sizeof(int));

    for(int idx = 0; idx < numbers->n; ++idx)
    {
        printf("Input element of %d cell.\n", idx);
        scanf("%d", &numbers->data[idx]);
    }
}

int main()
{
    numbers_t numbers;
    input_dates(&numbers);

    variation_elements(&numbers);

    return 0;
}
