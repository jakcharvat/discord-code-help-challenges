//
//  exports.cpp
//  WASM
//
//  Created by Jakub Charvat on 08.06.2021.
//

#ifndef DEBUG

#include "exports.hpp"


extern "C" {


int play(int row, int col)
{
    playAt(row, col);
    return (int)getPlayerAt(row, col);
}


int getWinDirection()
{
    return (int)(winInfo().direction);
}


int getCurrentPlayer()
{
    return (int)currentPlayer();
}

}
#endif
