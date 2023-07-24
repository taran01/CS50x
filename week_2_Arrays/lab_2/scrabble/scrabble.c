#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

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
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // convert input string to lowercase

    string s = word;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        s[i] = tolower(s[i]);
    }

    int score = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]))
        {
            score += POINTS[s[i] - 'a'];
        }
    }

    // get points for each character using switch
    // int points = 0;

    // for (int i = 0, n = strlen(s); i < n; i++)
    // {
    //     switch (s[i])
    //     {
    //         case 'a':
    //             points = points + POINTS[0];
    //             break;

    //         case 'b':
    //             points = points + POINTS[1];
    //             break;

    //         case 'c':
    //             points = points + POINTS[2];
    //             break;

    //         case 'd':
    //             points = points + POINTS[3];
    //             break;

    //         case 'e':
    //             points = points + POINTS[4];
    //             break;

    //         case 'f':
    //             points = points + POINTS[5];
    //             break;

    //         case 'g':
    //             points = points + POINTS[6];
    //             break;

    //         case 'h':
    //             points = points + POINTS[7];
    //             break;

    //         case 'i':
    //             points = points + POINTS[8];
    //             break;

    //         case 'j':
    //             points = points + POINTS[9];
    //             break;

    //         case 'k':
    //             points = points + POINTS[10];
    //             break;

    //         case 'l':
    //             points = points + POINTS[11];
    //             break;

    //         case 'm':
    //             points = points + POINTS[12];
    //             break;

    //         case 'n':
    //             points = points + POINTS[13];
    //             break;

    //         case 'o':
    //             points = points + POINTS[14];
    //             break;

    //         case 'p':
    //             points = points + POINTS[15];
    //             break;

    //         case 'q':
    //             points = points + POINTS[16];
    //             break;

    //         case 'r':
    //             points = points + POINTS[17];
    //             break;

    //         case 's':
    //             points = points + POINTS[18];
    //             break;

    //         case 't':
    //             points = points + POINTS[19];
    //             break;

    //         case 'u':
    //             points = points + POINTS[20];
    //             break;

    //         case 'v':
    //             points = points + POINTS[21];
    //             break;

    //         case 'w':
    //             points = points + POINTS[22];
    //             break;

    //         case 'x':
    //             points = points + POINTS[23];
    //             break;

    //         case 'y':
    //             points = points + POINTS[24];
    //             break;

    //         case 'z':
    //             points = points + POINTS[25];
    //             break;

    //         default:
    //             break;
    //     }
    //}

    return score;
}
