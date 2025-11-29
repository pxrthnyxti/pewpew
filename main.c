#include<stdio.h>
#include "board.h"
int main()
{
    TakePlayerName();
    DisplayBoard();
    while(1)
    {
        TakeInput();
    }
}