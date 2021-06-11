//
//  types.hpp
//  WASM
//
//  Created by Jakub Charvat on 10.06.2021.
//

#pragma once

#include <vector>

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3


//MARK: - Player
enum Player
{
    NoPlayer,
    Cross,
    Naught,
};

typedef std::vector<std::vector<Player>> Board;


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
    Board board;
    WinInfo win;
};
