//
//  gameManager.hpp
//  WASM
//
//  Created by Jakub Charvat on 06.06.2021.
//

#pragma once

#include <string>
#include <vector>

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3

#define BOARD_SIZE BOARD_HEIGHT][BOARD_WIDTH


//MARK: - Player
enum Player
{
    NoPlayer,
    Cross,
    Naught,
};


//MARK: - Win Direction
enum WinDirection
{
    NoDirection,
    Horizontal,
    Vertical,
    DiagonalForward,
    DiagonalBack
};


//MARK: - Win Info
struct WinInfo
{
    WinDirection direction;
    int winningRow;
    int winningCol;
};


//MARK: - TicTacToe State
struct TicTacToeState
{
    Player currentPlayer;
    Player board[BOARD_SIZE];
    WinInfo win;
};


TicTacToeState initialState();

std::string encode(const TicTacToeState &state);
TicTacToeState decode(const std::string &str);

//MARK: - Play
void playAt(int row, int col);

//MARK: - Win Checking
WinDirection checkWin(const Player board[BOARD_SIZE], const Player &player, const int &row, const int &col);

//MARK: - Getters
std::vector<std::vector<Player>> getBoard();
Player getPlayerAt(const int &row, const int &col);
WinInfo winInfo();

