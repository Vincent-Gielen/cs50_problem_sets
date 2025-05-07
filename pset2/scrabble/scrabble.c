#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string askWord(int speler);
int calculateScore(string word);

const char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const int score[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string words[2];
    for(int i = 0; i < 2; i++)
    {
        words[i] = askWord(i);
    }

    int score1 = calculateScore(words[0]);
    int score2 = calculateScore(words[1]);

    if(score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player %i wins!\n", score1 > score2 ? 1 : 2);
    }

}

string askWord(int speler)
{
    return get_string("Player %i: ", speler + 1);
}

int calculateScore(string word)
{
    int sum = 0;
    for(int i = 0, n = strlen(word); i < n; i++)
    {
        char letter = word[i];
        for(int j = 0; j < 26; j++)
        {
            if(toupper(letter) == letters[j])
            {
                sum += score[j];
                break;
            }
        }
    }
    return sum;
}
