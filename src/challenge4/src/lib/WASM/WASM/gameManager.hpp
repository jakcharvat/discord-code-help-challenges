//
//  gameManager.hpp
//  WASM
//
//  Created by Jakub Charvat on 06.06.2021.
//

#pragma once

#include <string>
#include <vector>

#include "types.hpp"


TicTacToeState initialState();

std::string encode(const TicTacToeState &state);
TicTacToeState decode(const std::string &str);

//MARK: - Play
void playAt(int row, int col);

//MARK: - Getters
std::vector<std::vector<Player>> getBoard();
Player getPlayerAt(const int &row, const int &col);
WinInfo winInfo();
Player currentPlayer();

