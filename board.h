#include <stdio.h>
#include "colors.h"
#include <string.h>
#include <stdlib.h>
// so that it becomes a 1 x 1 matrix;
extern int arr[25][25];
// names of people playing
extern char playerRED[100];
extern char playerWHITE[100];
// if 1 then RED plays first otherwiswe WHITE
extern int CurPlayerTurn;

void DisplayBoard();
void TakePlayerName();
int ValidatingInput(int row, int column);
void TakeInput();
