//
//  gameManager.cpp
//  WASM
//
//  Created by Jakub Charvat on 06.06.2021.
//

#include "gameManager.hpp"

#ifndef DEBUG
#include <emscripten/emscripten.h>
#endif

#include "minimax.hpp"
#include "sharedFunctions.hpp"


//MARK: - Local variables
TicTacToeState state = initialState();


//MARK: - Tic Tac Toe State
TicTacToeState initialState()
{
    TicTacToeState state { Cross, { }, { NoDirection, 0, 0 } };
    state.board.resize(3);
    for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
        state.board[i].resize(3);
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            state.board[i][j] = NoPlayer;
        }
    }
    return state;
}


int getBestMove()
{
    Coord bestMove = getBestMove(state);
    if (bestMove == CoordConsts::noCoord)
    {
        return -1;
    }
    
    return bestMove.first*10 + bestMove.second;
}




//MARK: - Play
void playAt(int row, int col)
{
    play(&state, row, col);
}


//MARK: - Getters
std::vector<std::vector<Player>> getBoard()
{
    return state.board;
}


Player getPlayerAt(const int &row, const int &col)
{
    return state.board[row][col];
}


WinInfo winInfo()
{
    return state.win;
}


Player currentPlayer()
{
    return state.currentPlayer;
}


TicTacToeState getState()
{
    return state;
}
