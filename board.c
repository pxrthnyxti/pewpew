#include <stdio.h>
#include "colors.h"
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include"logic.h"
int arr[25][25] = {0};
// names of people playing
char playerRED[100];
char playerWHITE[100];
// if 1 then RED plays first otherwiswe WHITE
int CurPlayerTurn = 1;

void DisplayBoard()
{
    printf("\033[2J\033[H");

    // COLUMN HEADERS
    printf("     ");
    for (int i = 1; i < 25; i++)
    {   
        if (i == 2 || i == 24)
            printf(CYAN_BOLD "    %02d  " RESET, i);
        else
            printf(CYAN_BOLD "%02d  " RESET, i);
    }
    printf("\n");

    for (int i = 1; i < 25; i++)
    {
        // TOP AND BOTTOM WHITE BORDER
        if (i == 2 || i == 24)
            printf(WHITE_BRIGHT "    ------------------------------------------------------------------------------------------------------\n" RESET);

        // LEFT ROW NUMBER
        printf(CYAN_BOLD "%02d" RESET, i);
        printf("    ");

        for (int j = 1; j < 25; j++)
        {
            // 4 CORNERS (PRINT SPACE BUT DO ***NOT*** CONTINUE)
            if ((i == 1 && j == 1) || (i == 1 && j == 24) ||
                (i == 24 && j == 1) || (i == 24 && j == 24))
            {
                printf("    ");   // exactly 4 spaces
                continue;         // safe here because corners have no other stuff
            }

            // FIXED BORDER (***EXACTLY 4 CHARACTERS***)
            if (j == 2 || j == 24)
            {
                printf(RED_BRIGHT "|   " RESET);  // "|   " = 4 chars, fixing drift
            }

            // CELL CONTENT (ALWAYS 4 CHARACTERS)
            if (arr[i][j] == 0)
                printf(".   ");
            else if (arr[i][j] == 1)
                printf(RED_BRIGHT "R   " RESET);
            else if (arr[i][j] == 2)
                printf(WHITE_BRIGHT "W   " RESET);
            else if (arr[i][j] == 3)
                printf(MAROON "R   " RESET);
            else if (arr[i][j] == 4)
                printf(GREY "W   " RESET);
        }
        printf("\n");
    }
}

void TakePlayerName()
{
    // const char* BOLD_CYAN = "\x1b[1;96m"; // Bold + Bright Cyan for the border
    // const char* MAGENTA = "\x1b[35m";     // Magenta for the text
    // const char* RESET = "\x1b[0m";        // Reset to default

    // Print the welcome message with colors
    printf("\n");
    printf(CYAN_BOLD "===================================================\n" RESET);
    printf("|          " MAGENTA "H E L L O   W E L C O M E" CYAN_BOLD "            |\n" RESET);
    printf("|               " MAGENTA "T O   T W I X T" CYAN_BOLD "                 |\n" RESET);
    printf(CYAN_BOLD "===================================================\n" RESET);
    printf("               " MAGENTA "~ Made by Parth ~" RESET "\n");
    printf("\n");

    printf(RED_BRIGHT "PLAYER RED , ENTER YOUR NAME : " WHITE_BRIGHT);
    fgets(playerRED, 100, stdin);
    // int c;
    // while ((c = getchar()) != '\n' && c != EOF) {}
    playerRED[strcspn(playerRED, "\n")] = 0;
    printf(WHITE_BRIGHT "PLAYER WHITE , ENTER YOUR NAME : " RESET);
    fgets(playerWHITE, 100, stdin);
    playerWHITE[strcspn(playerWHITE, "\n")] = 0;

    printf(CYAN_BOLD "===================================================\n" RESET);
    printf(CYAN_BOLD "WELCOME TO THE GAME" RED_BRIGHT " %s " CYAN_BOLD " AND " WHITE_BRIGHT " %s " CYAN_BOLD ". \n", playerRED, playerWHITE);
}

int ValidatingInput(int row, int column)
{
    if (row == 0 && column == 0)
    {
        printf(CYAN_BOLD "THANKYOU FOR PLAYING :)\n" RESET);
        exit(0);
    }
    if (row < 1 || row > 24 || column < 1 || column > 24 ||(row==1&&column==1)||(row==1&&column==24)||(row==24&&column==1)||(row==24&&column==24))
    {
        printf("PLEASE ENTER VALID COORDINATES :/\n");
        return 0;
    }
    if ((row == 1 || row == 24) && CurPlayerTurn != 2)
    {
        printf(WHITE_BRIGHT "SORRY BRUH — ONLY %s CAN PLAY HERE\n" RESET, playerWHITE);
        return 0;
    }
    if ((column == 1 || column == 24) && CurPlayerTurn != 1)
    {
        printf(RED_BRIGHT "SORRY BRUH — ONLY %s CAN PLAY HERE\n" RESET, playerRED);
        return 0;
    }
    if (arr[row][column] == 1 || arr[row][column] == 2)
    {
        printf("ALREADY OCCUPIED COORDINATES :/\n");
        return 0;
    }
    return 1;
}

void TakeInput()
{
    int row, column;
    while (1)
    {
        if (CurPlayerTurn == 1)
        {
            // red's turn
            printf(RED_BRIGHT "%s's" CYAN_BOLD " turn ( PLEASE ENTER THE COORDINATES ) : " RESET, playerRED);
        }
        else if (CurPlayerTurn == 2)
        {
            printf(WHITE_BRIGHT "%s's" CYAN_BOLD " turn ( PLEASE ENTER THE COORDINATES ) : " RESET, playerWHITE);
        }
        scanf("%d %d", &row, &column);
        if (ValidatingInput(row, column))
            break;
    }
    if (CurPlayerTurn == 1)
        arr[row][column] = 1;
    else
        arr[row][column] = 2;

    GenerateKnightNeighborsAndCheck(row, column);
    int w = CheckWinner();
    if (w == 1)
    {
        DisplayBoard();
        printf(RED_BRIGHT "\n%s (BLACK/RED) WINS THE GAME!!!\n" RESET, playerRED);
        exit(0);
    }
    else if (w == 2)
    {
        DisplayBoard();
        printf(WHITE_BRIGHT "\n%s (WHITE) WINS THE GAME!!!\n" RESET, playerWHITE);
        exit(0);
    }
    DisplayBoard();
    CurPlayerTurn = (CurPlayerTurn == 1) ? 2 : 1;
}
