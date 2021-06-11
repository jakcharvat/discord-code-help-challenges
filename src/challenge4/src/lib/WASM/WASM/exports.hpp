//
//  exports.hpp
//  WASM
//
//  Created by Jakub Charvat on 08.06.2021.
//

#ifndef DEBUG
#pragma once

#include <emscripten/emscripten.h>

#include "gameManager.hpp"


extern "C" {

EMSCRIPTEN_KEEPALIVE
int play(int row, int col);

EMSCRIPTEN_KEEPALIVE
int getWinDirection();

EMSCRIPTEN_KEEPALIVE
int getCurrentPlayer();

}

#endif
