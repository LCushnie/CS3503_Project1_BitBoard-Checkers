// main.c
// CS3503 Project 1 - BitBoard Checkers
// Author: Louis Cushnie

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "checkers.h"

int CoordToIndex(const char *coord) {
    if (strlen(coord) != 2) return -1;
    char col = toupper(coord[0]);
    int row = coord[1] - '1';
    if (col < 'A' || col > 'H' || row < 0 || row > 7) return -1;
    int colIndex = col - 'A';
    return row * 8 + colIndex;
}

int main(void) {
    GameState game;
    InitializeBoard(&game);

    char from[4], to[4];
    int fromIdx, toIdx;

    printf("=== BitBoard Checkers ===\n");
    PrintBoard(&game);

    while (1) {
        printf("\n%s's turn (enter move like C6 D5 or C6 E4): ",
               game.red_turn ? "Red" : "Black");

        if (scanf("%3s %3s", from, to) != 2) break;

        fromIdx = CoordToIndex(from);
        toIdx = CoordToIndex(to);

        if (fromIdx < 0 || toIdx < 0) {
            printf("❌ Invalid coordinates. Try again.\n");
            continue;
        }

        int diff = toIdx - fromIdx;
        int absdiff = diff >= 0 ? diff : -diff;

        if (absdiff==7 || absdiff== 9){
            MovePiece(&game, fromIdx, toIdx);
        } else if (absdiff==14 || absdiff==18) {
            CapturePiece(&game, fromIdx, toIdx);
        } else {
            printf("❌ Invalid move distance.\n");
            continue;
        }

        CheckPromotion(&game);
        PrintBoard(&game);

        if (CheckWinCondition(&game)) break;
    }

    printf("\nGame Over. Thanks for playing!\n");
    return 0;
}
