//
//  sharedFunctions.cpp
//  WASM
//
//  Created by Jakub Charvat on 10.06.2021.
//

#include "sharedFunctions.hpp"

#define NUM_NEIGHBOURS 4
#define COORD_SIZE 2


Player otherPlayer(const Player &player)
{
    switch (player)
    {
        case Player::Cross: return Player::Naught;
        case Player::Naught: return Player::Cross;
        case Player::NoPlayer: return Player::NoPlayer;
    }
}


void play(TicTacToeState *state, const int &row, const int &col)
{
    if (state->win.direction != NoDirection) { return; }
    if (row < 0 || row >= BOARD_HEIGHT) { return; }
    if (col < 0 || col >= BOARD_WIDTH) { return; }
    if (state->board[row][col] != NoPlayer) { return; }
    
    state->board[row][col] = state->currentPlayer;
    
    state->win.direction = checkWin(state->board, state->currentPlayer, row, col);
    if (state->win.direction != NoDirection)
    {
        state->win.winningRow = row;
        state->win.winningCol = col;
    } else {
        state->currentPlayer = otherPlayer(state->currentPlayer);
    }
}



Player playerAt(const Board &board, const int &row, const int &col)
{
    if (row < 0 || row >= BOARD_HEIGHT) { return NoPlayer; }
    if (col < 0 || col >= BOARD_WIDTH) { return NoPlayer; }
    
    return board[row][col];
}


WinDirection checkWin(const Board &board, const Player &player, const int &row, const int &col)
{
    int neighbours[NUM_NEIGHBOURS][COORD_SIZE] { {0, 1}, {1, 0}, {1, -1}, {1, 1} };
    
    for (int i = 0; i < NUM_NEIGHBOURS; ++i)
    {
        int addRow = neighbours[i][0];
        int addCol = neighbours[i][1];
        
        WinDirection direction = static_cast<WinDirection>(i+1);
        
        if (playerAt(board, row + addRow, col + addCol) == player) {
            // two in the original direction
            if (playerAt(board, row + 2*addRow, col + 2*addCol) == player) { return direction; }
            // one on either side of the newest block
            if (playerAt(board, row - addRow, col - addCol) == player) { return direction; }
        } else if (playerAt(board, row - addRow, col - addCol) == player) {
            // two in the opposite direction
            if (playerAt(board, row - 2*addRow, col - 2*addCol) == player) { return direction; }
        }
    }
    
    return NoDirection;
    
}
