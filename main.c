#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
int patterns[9][3] = {
    {1,2,3},
    {4,5,6},
    {7,8,9},
    {2,5,8},
    {1,4,7},
    {3,6,9},
    {1,5,9},
    {3,5,7},
};
char PLR_1_NAME = 'X';
char PLR_2_NAME = 'O';
char currentPattern[9] = { '0','0','0','0','0','0','0','0','0' };
int checkPattern();
int performAction(int player, int index);
int guessNextPosition(); // Fairly try to find a position to play in when on vs PC mode.
void performComputerAction();
void drawBoard();

int main()
{
    srand(time(NULL));
    int player = 1, winner = -1, choice;

    char sym;
    int mode; // 1 = 2 players mode, 2 = vs PC mode.
    printf("Type 1 for 2 Players mode or type 2 for vs PC mode?:  ");
    scanf_s("%d", &mode);
    do
    {
        drawBoard();
        sym = (player == 1) ? PLR_1_NAME : PLR_2_NAME;
        if (player == 2 && mode == 2) {
            performComputerAction();
            winner = checkPattern();
            player = player == 1 ? 2 : 1;
        }
        else
        {
            printf("Player %d, enter a position to place your %c symbol:  ", player, sym);
            scanf_s("%d", &choice);
            if (choice > 9 || choice < 0 || !choice) {
                printf("Invalid Choice.");
                _getch();
            }
            else {
                if (performAction(player, choice) == 1) {
                    winner = checkPattern();
                    player = player == 1 ? 2 : 1;
                }
                else {
                    winner = checkPattern();
                    printf("Invalid Choice.");
                    _getch();
                }
            }
        }
    } while (winner == -1);

    drawBoard();

    if (winner == 3 || winner == -1)
        printf("\aDraw!");
    else
        printf("\aPlayer %d wins!", winner);

    _getch();

    return 0;
}
int didPlayerMakePattern(int arr[], int p[])
{
    int totalFound = 0;
    int i;
    int k;
    int item;
    int item2;
    for (i = 0; i < 9; i++)
    {
        item = arr[i];
        for (k = 0; k < 3; k++)
        {
            item2 = p[k];
            if (item == item2)
            {
                totalFound += 1;
            }
        }
    }
    if (totalFound != 0 && totalFound >= 3)
        return 1;
    else
        return 0;
}
int checkPattern()
{
    int p1p[9] = {};
    int p2p[9] = {};
    int nextIndex = 0;
    int nextIndex2 = 0;
    int i;
    int k;
    int isDraw = 1;
    char player;
    int pos;
    for (i = 0; i < 9; i++)
    {
        if (currentPattern[i] != '0') {
            pos = i + 1;
            player = currentPattern[i];
            if (player == PLR_1_NAME) {
                p1p[nextIndex] = pos;
                nextIndex += 1;
            }
            else if (player == PLR_2_NAME) {
                p2p[nextIndex2] = pos;
                nextIndex2 += 1;
            }
            isDraw = 0;
        }
    }
    int *cpattern;
    for (k = 0; k < 8; k++) {
        cpattern = patterns[k];
        if (didPlayerMakePattern(p1p, cpattern) == 1)
        {
            return 1; // player 1 won
        }
        else if (didPlayerMakePattern(p2p, cpattern) == 1)
        {
            return 2; // player 2 won
        }
    }
    if (isDraw == 1) {
        return 3; // draw
    }
    return -1; // none won
}
int performAction(int player, int index)
{
    char sym = (player == 1) ? PLR_1_NAME : PLR_2_NAME;
    if (currentPattern[index - 1] == '0') {
        currentPattern[index - 1] = sym;
        return 1;
    }
    else {
        return 0;
    }
}
int guessNextPosition(int plr)
{
    int p1, p2, p3, i;

    char player = (plr == 1) ? PLR_1_NAME : PLR_2_NAME;
    for (i = 0; i < 9; i += 3) {
        p1 = currentPattern[i];
        p2 = currentPattern[i + 1];
        p3 = currentPattern[i + 2];
        if (p1 == p3 && p3 == player && p2 == '0')
            return i + 2;
        else if (p1 == p2 && p2 == player && p3 == '0')
            return i + 3;
        else if (p3 == p2 && p2 == player && p1 == '0')
            return i + 1;
    }
    p1 = currentPattern[0];
    p2 = currentPattern[4];
    p3 = currentPattern[8];
    if (p1 == p3 && p3 == player && p2 == '0')
        return 5;
    else if (p1 == p2 && p2 == player && p3 == '0')
        return 9;
    else if (p3 == p2 && p2 == player && p1 == '0')
        return 1;

    p1 = currentPattern[2];
    p2 = currentPattern[4];
    p3 = currentPattern[6];
    if (p1 == p3 && p3 == player && p2 == '0')
        return 5;
    else if (p1 == p2 && p2 == player && p3 == '0')
        return 7;
    else if (p3 == p2 && p2 == player && p1 == '0')
        return 3;
    if (currentPattern[patterns[3][0] - 1] == currentPattern[patterns[3][2] - 1] && currentPattern[patterns[3][2] - 1] == player && currentPattern[patterns[3][1] - 1] == '0')
        return patterns[3][1];
    else if (currentPattern[patterns[3][0] - 1] == currentPattern[patterns[3][1] - 1] && currentPattern[patterns[3][1] - 1] == player && currentPattern[patterns[3][2] - 1] == '0')
        return patterns[3][2];
    else if (currentPattern[patterns[3][1] - 1] == currentPattern[patterns[3][2] - 1] && currentPattern[patterns[3][2] - 1] == player && currentPattern[patterns[3][0] - 1] == '0')
        return patterns[3][0];

    if (currentPattern[patterns[4][0] - 1] == currentPattern[patterns[4][2] - 1] && currentPattern[patterns[4][2] - 1] == player && currentPattern[patterns[4][1] - 1] == '0')
        return patterns[4][1];
    else if (currentPattern[patterns[4][0] - 1] == currentPattern[patterns[4][1] - 1] && currentPattern[patterns[4][1] - 1] == player && currentPattern[patterns[4][2] - 1] == '0')
        return patterns[4][2];
    else if (currentPattern[patterns[4][1] - 1] == currentPattern[patterns[4][2] - 1] && currentPattern[patterns[4][2] - 1] == player && currentPattern[patterns[4][0] - 1] == '0')
        return patterns[4][0];

    if (currentPattern[patterns[5][0] - 1] == currentPattern[patterns[5][2] - 1] && currentPattern[patterns[5][2] - 1] == player && currentPattern[patterns[5][1] - 1] == '0')
        return patterns[5][1];
    else if (currentPattern[patterns[5][0] - 1] == currentPattern[patterns[5][1] - 1] && currentPattern[patterns[5][1] - 1] == player && currentPattern[patterns[5][2] - 1] == '0')
        return patterns[5][2];
    else if (currentPattern[patterns[5][1] - 1] == currentPattern[patterns[5][2] - 1] && currentPattern[patterns[5][2] - 1] == player && currentPattern[patterns[5][0] - 1] == '0')
        return patterns[5][0];

    return -1; // not found
}
int randmonNum(int min, int max)
{
    return min + (int)(rand() / (double)(RAND_MAX + 1) * (max - min + 1));
}
void performComputerAction()
{
    int freePositions[9] = {};
    int nextPos = 0;
    int lastPos = -1;
    int i;
    for (i = 0; i < 9; i++) {
        char p = currentPattern[i];
        if (p == '0') {
            freePositions[nextPos] = i + 1;
            lastPos = nextPos;
            nextPos += 1;
        }
    }
    int p1pos = guessNextPosition(1);
    int p2pos = guessNextPosition(2);
    int defend_or_random = randmonNum(0, 1);

    int usablepos = p2pos;
    if (p2pos == -1 && defend_or_random == 1) // 1 = defend, 0 = random position
    {
        usablepos = p1pos;
        printf("11ch\n");
    }
    if (p1pos == -1 || defend_or_random == 0)
    {
        if (lastPos != -1) {
            usablepos = freePositions[randmonNum(0, lastPos)];
            printf("22ch\n");
        }
    }
    if (usablepos != -1)
        currentPattern[usablepos - 1] = PLR_2_NAME;
}
char getSquareValue(int id)
{
    return (currentPattern[id - 1] == '0' ? id + '0' : currentPattern[id - 1]);
}
void drawBoard()
{
    system("cls");
    printf("Player 1 (%c)  -  Player 2 (%c)\n\n", PLR_1_NAME, PLR_2_NAME);


    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", getSquareValue(1), getSquareValue(2), getSquareValue(3));

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", getSquareValue(4), getSquareValue(5), getSquareValue(6));

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", getSquareValue(7), getSquareValue(8), getSquareValue(9));

    printf("     |     |     \n\n");
}
