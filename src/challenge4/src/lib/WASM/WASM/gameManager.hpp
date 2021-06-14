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


//MARK: - Play
void playAt(int row, int col);
void resetGame();

int getBestMove(int difficulty);

//MARK: - Getters
std::vector<std::vector<Player>> getBoard();
Player getPlayerAt(const int &row, const int &col);
WinInfo winInfo();
Player currentPlayer();
TicTacToeState getState();
bool isTie();

