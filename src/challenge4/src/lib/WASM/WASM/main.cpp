//
//  main.cpp
//  WASM
//
//  Created by Jakub Charvat on 06.06.2021.
//


#ifdef DEBUG

#include <iostream>

#include "gameManager.hpp"
#include "exports.hpp"

typedef std::vector<std::vector<Player>> Board;


std::string playerStr(const Player &player)
{
    switch (player)
    {
        case NoPlayer: return " ";
        case Cross: return "X";
        case Naught: return "O";
    }
}

//MARK: - Board String Rep
std::string horizontalLine(const std::string &start, const std::string &mid, const std::string &end)
{
    std::string rep = "";
    rep += start;
    for (int i = 0; i < BOARD_WIDTH; ++i)
    {
        if (i != 0) { rep += mid; }
        
        rep += "───";
    }
    rep += end + "\n";
    return rep;
}


std::string spacerLine()
{
    std::string rep = "";
    for (int i = 0; i < BOARD_WIDTH; ++i) { rep += "│   "; }
    rep += "│\n";
    return rep;
}


std::string boardRep(const Board &board)
{
    std::string rep = "";
    
    // Draw the top line
    rep += horizontalLine("┌", "┬", "┐");
    
    // Draw the boxes
    for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
        if (i != 0) { rep += horizontalLine("├", "┼", "┤"); }
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            rep += "│ " + playerStr(board[i][j]) + " ";
        }
        rep += "│\n";
    }
    
    rep += horizontalLine("└", "┴", "┘");
    
    return rep;
}


int main() {
//    std::cout << playAt(0, 0) << std::endl;
//    std::cout << playAt(1, 0) << std::endl;
//    std::cout << playAt(0, 1) << std::endl;
//    std::cout << getWinInfo() << std::endl;
    
    
    while (true)
    {
        std::cout << "Current state:" << std::endl;
        std::cout << boardRep(getBoard()) << std::endl;
        std::cout << std::endl;
        std::cout << "[row] [col] > ";
        std::string input;
        std::cin >> input;
        
        if (input == "q" || input == "quit") { break; }
        int row = std::stoi(input);
        
        std::cin >> input;
        if (input == "q" || input == "quit") { break; }
        int col = std::stoi(input);
        
        playAt(row, col);
    }
    
    std::cout << std::endl << "Game Finished" << std::endl;
}

#else

int main() {
    
}

#endif
