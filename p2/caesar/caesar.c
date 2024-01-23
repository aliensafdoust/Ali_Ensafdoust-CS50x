#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



int main(int argc, string argv[])
{
    //Have an input
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int count = strlen(argv[1]);
    //Input should not be alphabetical
    for (int k = 0; k < count ; k++)
    {
        if ((argv[1][k] >= 65 && argv[1][k] <= 90) || (argv[1][k] >= 97 && argv[1][k] <= 122))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //convert string to int
    int key = atoi(argv[1]);

    string text = get_string("plaintext:  ");

    char ca;
    int c = strlen(text), plan;
    char cip[c];
    //The main part of the code
    for (int p = 0; p < c; p++)
    {
        plan = text[p];

        if (isalpha(plan))
        {
            ca = plan + key % 26;
            //If it was except numbers or signs
            if (!(islower(ca) || isupper(ca)))
            {
                ca = ca - 26;
            }
        }
        else
        {
            ca = plan;
        }

        cip[p] = ca;
    }
    cip[c] = '\0';
    //Finally, print the array as a string
    printf("ciphertext: %s\n", cip);
    return 0;

}