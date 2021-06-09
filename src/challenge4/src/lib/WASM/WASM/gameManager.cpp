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

#define NUM_NEIGHBOURS 4
#define COORD_SIZE 2


//MARK: - Local variables
TicTacToeState state = initialState();


//MARK: - Player
Player otherPlayer(const Player &player)
{
    switch (player)
    {
        case Player::Cross: return Player::Naught;
        case Player::Naught: return Player::Cross;
        case Player::NoPlayer: return Player::NoPlayer;
    }
}


//MARK: - Tic Tac Toe State
TicTacToeState initialState()
{
    TicTacToeState state { Cross, { }, { NoDirection, 0, 0 } };
    for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
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
    if (state.win.direction != NoDirection) { return; }
    if (row < 0 || row >= BOARD_HEIGHT) { return; }
    if (col < 0 || col >= BOARD_WIDTH) { return; }
    if (state.board[row][col] != NoPlayer) { return; }
    
    state.board[row][col] = state.currentPlayer;
    
    state.win.direction = checkWin(state.board, state.currentPlayer, row, col);
    if (state.win.direction != NoDirection)
    {
        state.win.winningRow = row;
        state.win.winningCol = col;
    } else {
        state.currentPlayer = otherPlayer(state.currentPlayer);
    }
}


//MARK: - Win Checking
Player playerAt(const Player board[BOARD_SIZE], const int &row, const int &col)
{
    if (row < 0 || row >= BOARD_HEIGHT) { return NoPlayer; }
    if (col < 0 || col >= BOARD_WIDTH) { return NoPlayer; }
    
    return board[row][col];
}


WinDirection checkWin(const Player board[BOARD_SIZE], const Player &player, const int &row, const int &col)
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


//MARK: - Getters
std::vector<std::vector<Player>> getBoard()
{
    std::vector<std::vector<Player>> v;
    v.reserve(BOARD_HEIGHT);
    
    for (auto &row : state.board)
    {
        std::vector<Player> r;
        r.reserve(BOARD_WIDTH);
        for (auto &player : row)
        {
            r.push_back(player);
        }
        v.push_back(r);
    }
    
    return v;
}


Player getPlayerAt(const int &row, const int &col)
{
    return state.board[row][col];
}


WinInfo winInfo()
{
    return state.win;
}
