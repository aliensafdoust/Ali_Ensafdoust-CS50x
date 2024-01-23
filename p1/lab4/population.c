#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int numb1;
    do
    {
        numb1 = get_int("Start size: ");
    }
    while (numb1 < 9);

    // TODO: Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < numb1);

    // TODO: Calculate number of years until we reach threshold
    int yeear = 0;

    while (numb1 < end_size)
    {
        numb1 += (numb1 / 3) - (numb1 / 4);
        yeear++;
    }
    // TODO: Print number of years

    printf("Years: %i\n", yeear);
}
