#include <cs50.h>
#include <stdio.h>

int counter(long n);
int calculate(long x);

int main(void)
{
    long long_number_1 = get_long("Number: ");

    int cou = counter(long_number_1);

    if (cou != 16 && cou != 15 && cou != 13)
    {
        printf("INVALID\n");
        return 0;
    }

    int total = calculate(long_number_1);

    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    long visa = long_number_1;

    // Visa uses 13- and 16-digit numbers.
    // MasterCard uses 16-digit numbers.
    if (cou == 16 || cou == 13)
    {

        if (cou == 13)
        {
            for (int V = 0; V < 12; V++)
            {
                visa /= 10;
            }
        }

        else if (cou == 16)
        {
            for (int M = 0; M < 14; M++)
            {
                long_number_1 /= 10;
            }
            for (int V = 0; V < 15; V++)
            {
                visa /= 10;
            }
        }

        if (visa == 4)
        {
            printf("VISA\n");
            return 0;
        }
        else if (long_number_1 == 51 || long_number_1 == 52 || long_number_1 == 53 || long_number_1 == 54 || long_number_1 == 55)
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    // American Express uses 15-digit numbers.
    if (cou == 15)
    {
        for (int A = 0; A < 13; A++)
        {
            long_number_1 /= 10;
        }
        if (long_number_1 == 34 || long_number_1 == 37)
        {
            printf("AMEX\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
}

int counter(long n)
{
    int i = 0;

    while (n > 0)
    {
        n /= 10;
        i++;
    }

    return i;
}

int calculate(long x)
{

    int mod_1, mod_2, list_1 = 0, list_2 = 0, div_1, div_2;

    do
    {
        mod_1 = x % 10;
        x = x / 10;
        list_1 += mod_1;

        mod_2 = x % 10;
        x = x / 10;
        mod_2 *= 2;

        if (mod_2 >= 10)
        {
            div_1 = mod_2 % 10;
            div_2 = mod_2 / 10;
            list_2 += div_1 + div_2;
        }
        else
        {
            list_2 += mod_2;
        }
    }
    while (x > 0);

    int total = list_1 + list_2;

    return total;
}