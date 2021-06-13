//
//  sharedFunctions.hpp
//  WASM
//
//  Created by Jakub Charvat on 10.06.2021.
//

#pragma once

#include <string>

#include "types.hpp"


Player otherPlayer(const Player &player);


std::string encode(const TicTacToeState &state);
TicTacToeState decode(const std::string &str);


void play(TicTacToeState *state, const int &row, const int &col);
WinDirection checkWin(const Board &board, const Player &player, const int &row, const int &col);
