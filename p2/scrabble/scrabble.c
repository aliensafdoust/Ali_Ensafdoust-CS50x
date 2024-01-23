#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
// This array contains all uppercase letters
char LOW[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
// This array contains all uppercase letters
char UPPER[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};


int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    // player 1
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    // player 2
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    // equal
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int count = strlen(word), score = 0;
    // This loop is for scrolling words
    for (int i = 0; i < count ; i++)
    {
        // This loop is for scrolling through the alphabet
        for (int j = 0 ; j < 26 ; j++)
        {
            if (word[i] == LOW [j])
            {
                score += POINTS[j];
            }
            else if (word[i] == UPPER[j])
            {
                score += POINTS[j];
            }
        }
    }

    return score;

}
