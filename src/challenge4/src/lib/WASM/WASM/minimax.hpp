//
//  minimax.hpp
//  WASM
//
//  Created by Jakub Charvat on 10.06.2021.
//

#pragma once

#include <utility>

#include "types.hpp"

typedef std::pair<int, int> Coord;


Coord getBestMove(const TicTacToeState &state, const int &difficulty);


struct CoordConsts
{
    static Coord noCoord;
};
