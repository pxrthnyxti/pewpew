#include <stdio.h>
#include <stdlib.h>
#include "logic.h"
#include "board.h"
Node adj[25][25][8];
int adjCount[25][25] = {0};

// -----------------------------------------------------------
// PURE KNIGHT CHECK
// -----------------------------------------------------------
int IsKnightMove(int r1, int c1, int r2, int c2)
{
    int dr = abs(r1 - r2);
    int dc = abs(c1 - c2);
    return ((dr == 1 && dc == 2) || (dr == 2 && dc == 1));
}
void GenerateKnightNeighborsAndCheck(int r, int c)
{
    int color = arr[r][c];

    // Only accept original or recolored versions:
    // Red  = 1 (original), 3 (connected)
    // White = 2 (original), 4 (connected)
    int isRed   = (color == 1 || color == 3);
    int isWhite = (color == 2 || color == 4);

    if (!isRed && !isWhite)
        return;

    // Knight move offsets
    static const int dx[8] = {  2,  2, -2, -2,  1,  1, -1, -1 };
    static const int dy[8] = {  1, -1,  1, -1,  2, -2,  2, -2 };

    for (int k = 0; k < 8; k++)
    {
        int nr = r + dx[k];
        int nc = c + dy[k];

        // Bounds check
        if (nr < 1 || nr > 24 || nc < 1 || nc > 24)
            continue;

        int neighbor = arr[nr][nc];

        // Match only same-color groups
        if (isRed)
        {
            if (!(neighbor == 1 || neighbor == 3))
                continue;
        }
        else // white piece
        {
            if (!(neighbor == 2 || neighbor == 4))
                continue;
        }

        // Actual knight check (just for safety, although dx/dy already guarantees it)
        if (!IsKnightMove(r, c, nr, nc))
            continue;

        // ---------------------------
        // VALID CONNECTION FOUND
        // ---------------------------

        // Convert original pieces to connected ones
        if (isRed)
        {
            if (arr[r][c] == 1)     arr[r][c] = 3;
            if (arr[nr][nc] == 1)   arr[nr][nc] = 3;
        }
        else
        {
            if (arr[r][c] == 2)     arr[r][c] = 4;
            if (arr[nr][nc] == 2)   arr[nr][nc] = 4;
        }

        // Add the chain link to your adjacency graph
        AddConnection(r, c, nr, nc);

        // IMPORTANT:
        // DO NOT return — we must allow multiple connections.
    }
}
void AddPeg(int r, int c, int color)
{
    arr[r][c] = color;
    GenerateKnightNeighborsAndCheck(r, c);
}
void AddConnection(int r1, int c1, int r2, int c2)
{
    // prevent duplicates
    for (int i = 0; i < adjCount[r1][c1]; i++)
    {
        if (adj[r1][c1][i].r == r2 && adj[r1][c1][i].c == c2)
            return; // already exists
    }

    adj[r1][c1][adjCount[r1][c1]].r = r2;
    adj[r1][c1][adjCount[r1][c1]].c = c2;
    adjCount[r1][c1]++;

    adj[r2][c2][adjCount[r2][c2]].r = r1;
    adj[r2][c2][adjCount[r2][c2]].c = c1;
    adjCount[r2][c2]++;
}
// WIN DETECTION

int visited[25][25];
int dfs_black(int r, int c)
{
    if (c == 24)
        return 1; // black reached right side

    visited[r][c] = 1;

    for (int i = 0; i < adjCount[r][c]; i++)
    {
        int rr = adj[r][c][i].r;
        int cc = adj[r][c][i].c;

        if (!visited[rr][cc] && (arr[rr][cc] == 3)) // 3 = black (maroon)
        {
            if (dfs_black(rr, cc))
                return 1;
        }
    }

    return 0;
}
int dfs_white(int r, int c)
{
    if (r == 24)
        return 1; // white reached bottom

    visited[r][c] = 1;

    for (int i = 0; i < adjCount[r][c]; i++)
    {
        int rr = adj[r][c][i].r;
        int cc = adj[r][c][i].c;

        if (!visited[rr][cc] && (arr[rr][cc] == 4)) // 4 = white (grey)
        {
            if (dfs_white(rr, cc))
                return 1;
        }
    }

    return 0;
}
int CheckWinner()
{
    // ---------- BLACK: left (col=0) to right (col=24) ----------
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 25; j++)
            visited[i][j] = 0;

    for (int r = 0; r < 25; r++)
    {
        if (arr[r][0] == 3) // black peg present in left column
        {
            if (dfs_black(r, 0))
                return 1; // BLACK WINS
        }
    }

    // ---------- WHITE: top (row=0) to bottom (row=24) ----------
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 25; j++)
            visited[i][j] = 0;

    for (int c = 0; c < 25; c++)
    {
        if (arr[0][c] == 4) // white peg in top row
        {
            if (dfs_white(0, c))
                return 2; // WHITE WINS
        }
    }

    return 0; // no winner yet
}
