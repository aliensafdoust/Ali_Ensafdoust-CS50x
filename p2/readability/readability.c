#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int math(int c, string tx);

int main(void)
{
    //main entrance
    string txt = get_string("Text : ");

    //Find the number of characters in a string
    int count =  strlen(txt);

    int in = math(count, txt);
    //If the resulting index number is 16 or higher
    if (in >= 16)
    {
        printf("Grade 16+\n");
    }
    //If the index number is less than 1
    else if (in < 1)
    {
        printf("Before Grade 1\n");
    }
    //the original value
    else
    {
        printf("Grade %i\n", in);
    }
}



int math(int c, string tx)
{
    float le = 0, wo = 1, sen = 0;

    //Comparison with the help of ASCII-Table
    for (int i = 0; i < c; i++)
    {
        //Number of letters
        if ((tx[i] >= 65 && tx[i] <= 90) || (tx[i] >= 97 && tx[i] <= 122))
        {
            le++;
        }
        //Number of words
        else if (tx[i] == 32)
        {
            wo++;
        }
        //Number of sentences
        else if (tx[i] == 33 || tx[i] == 63 || tx[i] == 46)
        {
            sen++;
        }
    }

    float L = 100 * (le / wo);
    float S = 100 * (sen / wo);
    //Final calculation
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}