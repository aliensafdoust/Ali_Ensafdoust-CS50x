#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // getting name
    string name = get_string("What's your name? ");
    // order to print
    printf("hello, %s\n", name);
}