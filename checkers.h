// checkers.h
// CS3503 Project 1 - BitBoard Checkers
// Author: Louis Cushnie

#include <stdio.h>
#include <stdbool.h>

#ifndef CHECKERS_H
#define CHECKERS_H

#define MOVE_NORTHEAST 9
#define MOVE_NORTHWEST 7
#define MOVE_SOUTHEAST 7
#define MOVE_SOUTHWEST 9

#define RED_KING_ROW    0x00000000000000FFULL
#define BLACK_KING_ROW  0xFF00000000000000ULL

typedef struct {
    unsigned long long red_pieces;
    unsigned long long black_pieces;
    unsigned long long red_kings;
    unsigned long long black_kings;
    bool red_turn;
} GameState;

void InitializeBoard(GameState *game);
void PrintBoard(const GameState *game);

int  IsOccupied(const GameState *game, int position);
void CheckPromotion(GameState *game);

void MovePiece(GameState *game, int from, int to);
int  CapturePiece(GameState *game, int from, int to);
bool CheckWinCondition(const GameState *game);
#endif

