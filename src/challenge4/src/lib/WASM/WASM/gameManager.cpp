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


std::string encode(const TicTacToeState &state)
{
    std::string currPlayer = std::to_string(state.currentPlayer);
    std::string boardRep = "";
    
    for (auto &row : state.board)
    {
        for (auto &player : row)
        {
            boardRep += std::to_string(player);
        }
    }
    
    std::string winDir = std::to_string(state.win.direction);
    std::string winRow = std::to_string(state.win.winningRow);
    std::string winCol = std::to_string(state.win.winningCol);
    
    return currPlayer + boardRep + winDir + winRow + winCol;
}


int ctoi(const char &c)
{
    return (c - '0');
}


TicTacToeState decode(const std::string &str)
{
    Player currPlayer = static_cast<Player>(ctoi(str[0]));
    
    WinDirection winDirection = static_cast<WinDirection>(ctoi(str[10]));
    int winRow = ctoi(str[11]);
    int winCol = ctoi(str[12]);
    
    TicTacToeState state { currPlayer, { }, { winDirection, winRow, winCol } };
    
    for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            state.board[i][j] = static_cast<Player>(ctoi(str[i*BOARD_WIDTH + j + 1]));
        }
    }
    
    return state;
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
