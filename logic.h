#ifndef LOGIC_H
#define LOGIC_H

typedef struct {
    int r, c;
} Node;

extern Node adj[25][25][8];   
extern int adjCount[25][25]; 

void AddConnection(int r1, int c1, int r2, int c2);
void AddPeg(int r, int c, int color);
int IsKnightMove(int r1, int c1, int r2, int c2);
void GenerateKnightNeighborsAndCheck(int r, int c);
int CheckWinner();

#endif
