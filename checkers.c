// checkers.c
// CS3503 Project 1 - BitBoard Checkers
// Author: Louis Cushnie

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "checkers.h"
#include "bitops.h"

void InitializeBoard(GameState *game) {
    game->red_pieces = 0ULL;
    game->black_pieces = 0ULL;
    game->red_kings = 0ULL;
    game->black_kings = 0ULL;
    game->red_turn = true;

    const unsigned long long DARK_SQUARES = 0x55AA55AA55AA55AAULL;

    unsigned long long bottom_rows = 0x0000000000FFFFFFULL;
    game->black_pieces = bottom_rows & DARK_SQUARES;

    unsigned long long top_rows = 0xFFFFFF0000000000ULL;
    game->red_pieces = top_rows & DARK_SQUARES;
}

void PrintBoard(const GameState *game) {
    printf("\n    A B C D E F G H\n");
    printf("   -----------------\n");

    for (int row = 7; row >= 0; row--){
        printf("%d | ", row + 1);
        for (int col = 0; col < 8; col++){
            int pos = row * 8 + col;
            unsigned long long mask = 1ULL << pos;

            if (game->red_pieces & mask)
                printf("r ");
            else if (game->black_pieces & mask)
                printf("b ");
            else if (game->red_kings & mask)
                printf("R ");
            else if (game->black_kings & mask)
                printf("B ");
            else
                printf(". ");
        }
        printf("| %d\n", row + 1);
    }

    printf("   -----------------\n");
    printf("    A B C D E F G H\n");
    printf("\nCurrent turn: %s\n", game->red_turn ? "Red" : "Black");
}

int IsOccupied(const GameState *game, int position) {
    if (position < 0 || position > 63) return 0;
    unsigned long long all =
        game->red_pieces | game->black_pieces |
        game->red_kings | game->black_kings;
    return (int)((all >> position) & 1ULL);
}

void CheckPromotion(GameState *game) {
    unsigned long long promoted_reds = game->red_pieces & RED_KING_ROW;
    if (promoted_reds){
        game->red_pieces &= ~promoted_reds;
        game->red_kings |= promoted_reds;
        printf("👑 Red piece promoted to KING!\n");
    }

    unsigned long long promoted_blacks = game->black_pieces & BLACK_KING_ROW;
    if (promoted_blacks) {
        game->black_pieces &= ~promoted_blacks;
        game->black_kings |= promoted_blacks;
        printf("👑 Black piece promoted to KING!\n");
    }
}

bool CheckWinCondition(const GameState *game) {
    if ((game->red_pieces | game->red_kings) == 0ULL) {
        printf("🏁 Black wins! Red has no pieces left.\n");
        return true;
    }
    if ((game->black_pieces | game->black_kings) == 0ULL) {
        printf("🏁 Red wins! Black has no pieces left.\n");
        return true;
    }
    return false;
}

void MovePiece(GameState *game, int from, int to) {
    unsigned long long mask_from = 1ULL << from;
    unsigned long long mask_to   = 1ULL << to;

    if (IsOccupied(game, to)) {
        printf("❌ Invalid move: destination occupied.\n");
        return;
    }

    // Move red
    if (game->red_turn && (game->red_pieces & mask_from)) {
        game->red_pieces &= ~mask_from; 
        game->red_pieces |= mask_to;
        CheckPromotion(game);
        if (CheckWinCondition(game)) {
            printf("Game over.\n");
            return;
        }
        game->red_turn = false;
    }

    // Move black
    else if (!game->red_turn && (game->black_pieces & mask_from)) {
        game->black_pieces &= ~mask_from;
        game->black_pieces |= mask_to;
        CheckPromotion(game);
        if (CheckWinCondition(game)) {
            printf("Game over.\n");
            return;
        }
        game->red_turn = true;
    }

    else {
        printf("❌ Invalid move: no piece at that square.\n");
    }
}


int CapturePiece(GameState *game, int from, int to) {
    if (from < 0 || from > 63 || to < 0 || to > 63){
        printf("Invalid indices (out of 0..63).\n");
        return 0;
    }

    int diff = to - from;
    int absdiff = diff >= 0 ? diff : -diff;

    if (!(absdiff == 14 || absdiff == 18)) {
        printf("Invalid capture: not a two-square diagonal jump.\n");
        return 0;
    }

    int over = (from + to) / 2;

    unsigned long long mfrom = 1ULL << from;
    unsigned long long mover = 1ULL << over;
    unsigned long long mto   = 1ULL << to;

    if (IsOccupied(game, to)) {
        printf("Invalid capture: destination occupied.\n");
        return 0;
    }

    if (game->red_turn){
        int isKing = (game->red_kings & mfrom) ? 1 : 0;
        int isMan  = (game->red_pieces & mfrom) ? 1 : 0;
        if (!isKing && !isMan) {
            printf("Invalid capture: no red piece at 'from'.\n");
            return 0;
        }
        
        int oppMan = (game->black_pieces & mover) ? 1 : 0;
        int oppKing = (game->black_kings & mover) ? 1 : 0;
        if (!oppMan && !oppKing) {
            printf("Invalid capture: nothing to capture.\n");
            return 0;
        }
        
        if (!isKing && !(to < from)) {
            printf("Invalid capture: red man cannot move backwards.\n");
            return 0;
        }

        if (isKing) {
            game->red_kings &= ~mfrom;
            game->red_kings |= mto;
        } else {
            game->red_pieces &= ~mfrom;
            game->red_pieces |= mto;
        }

        if (oppMan) game->black_pieces &= ~mover;
        else game->black_kings &= ~mover;

        game->red_turn = false;
        printf("Red captured successfully (from %d to %d over %d).\n", from, to, over);
        CheckPromotion(game);
        if (CheckWinCondition(game)) {
            printf("Game over.\n");
            return;
        }
        return 1;
        
    } else{
        int isKing = (game->black_kings & mfrom) ? 1 : 0;
        int isMan  = (game->black_pieces & mfrom) ? 1 : 0;
        if (!isKing && !isMan) {
            printf("Invalid capture: no black piece at 'from'.\n");
            return 0;
        }

        int oppMan = (game->red_pieces & mover) ? 1 : 0;
        int oppKing = (game->red_kings & mover) ? 1 : 0;
        if (!oppMan && !oppKing) {
            printf("Invalid capture: nothing to capture.\n");
            return 0;
        }

        if (!isKing && !(to > from)) {
            printf("Invalid capture: black man cannot move backwards.\n");
            return 0;
        }

        if (isKing) {
            game->black_kings &= ~mfrom;
            game->black_kings |= mto;
        } else {
            game->black_pieces &= ~mfrom;
            game->black_pieces |= mto;
        }

        if (oppMan) game->red_pieces &= ~mover;
        else game->red_kings &= ~mover;

        game->red_turn = true;
        printf("Black captured successfully (from %d to %d over %d).\n", from, to, over);
        CheckPromotion(game);
        if (CheckWinCondition(game)) {
            printf("Game over.\n");
            return;
        }
        return 1;
    }
}

