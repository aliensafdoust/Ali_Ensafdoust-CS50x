#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h > 8 || h < 1);

    for (int ih = 0; ih < h; ih++)
    {
        for (int i = 0; i < h - ih; i++)
        {
            printf(" ");
        }
        for (int shl = 0; shl < ih; shl++)
        {
            printf("#");
        }

        printf(" ");

        for (int shr = 0; shr < ih; shr++)
        {
            printf("#");
        }
        printf("\n");
    }
}