//
//  minimax.cpp
//  WASM
//
//  Created by Jakub Charvat on 10.06.2021.
//

#include "minimax.hpp"

#include <vector>
#include <time.h>

#ifdef DEBUG
#include <iostream>
#endif

#include "sharedFunctions.hpp"

#define WIN_SCORE 100
#define TWO_IN_ROW_SCORE 10


// Cross tries to maximise score, naught tries to minimise it

int scoreForLine(Player a, Player b, Player c)
{
    if (b == NoPlayer)
    {
        return 0;
    }
    
    if (a == b && b == c)
    {
        return a == Cross ? WIN_SCORE : -WIN_SCORE;
    }
    
    if (a == b || b == c)
    {
//        return b == Cross ? TWO_IN_ROW_SCORE : -TWO_IN_ROW_SCORE;
    }
    
    return 0;
}


#ifdef DEBUG
std::ostream &operator << (std::ostream &os, const Board &board)
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            switch (board[row][col])
            {
                case NoPlayer: os << " "; break;
                case Cross: os << "X"; break;
                case Naught: os << "O"; break;
            }
        }
        std::cout << std::endl;
    }
    return os;
}
#endif


//MARK: - Evaluate Board
int evaluateBoard(const Board &board)
{
#ifdef DEBUG
    std::cout << board << std::endl;
#endif
    int score = 0;
    // Check rows
    for (int row = 0; row < BOARD_HEIGHT; ++row)
    {
        score += scoreForLine(board[row][0], board[row][1], board[row][2]);
    }
    
    // Check cols
    for (int col = 0; col < BOARD_WIDTH; ++col)
    {
        score += scoreForLine(board[0][col], board[1][col], board[2][col]);
    }
    
    // Check diagonals
    score += scoreForLine(board[0][0], board[1][1], board[2][2]);
    score += scoreForLine(board[2][0], board[1][1], board[0][2]);
    
#ifdef DEBUG
    std::cout << score << std::endl << "------------------------------" << std::endl << std::endl;
#endif
    
    return score;
}


//MARK: - Generate Moves
std::vector<Coord> generateMoves(const Board &board)
{
    std::vector<Coord> possibleMoves;
    for (int row = 0; row < BOARD_HEIGHT; ++row)
    {
        for (int col = 0; col < BOARD_WIDTH; ++col)
        {
            if (board[row][col] == NoPlayer)
            {
                possibleMoves.push_back({ row, col });
            }
        }
    }
    
    return possibleMoves;
}


bool isBetter(int oldScore, int newScore, const Player &player)
{
    return player == Cross ? newScore > oldScore : newScore < oldScore;
}


std::pair<Coord, int> evalBestMove(const TicTacToeState &state, const int &difficulty)
{
    std::vector<Coord> possibleMoves = generateMoves(state.board);
    
    if (possibleMoves.empty())
    {
        return { CoordConsts::noCoord, 0 };
    }
    
    Coord bestMove = CoordConsts::noCoord;
    int bestScore = state.currentPlayer == Cross ? INT_MIN : INT_MAX;
    
    for (auto move: possibleMoves)
    {
        int row = move.first, col = move.second;
        TicTacToeState stateCopy = state;
        play(&stateCopy, row, col);
        if (stateCopy.win.direction != NoDirection)
        {
            int score = evaluateBoard(stateCopy.board);
            if (isBetter(bestScore, score, stateCopy.currentPlayer))
            {
                bestScore = score;
                bestMove = move;
            }
            continue;
        }
        
        std::pair<Coord, int> value = evalBestMove(stateCopy, difficulty);
        
        if (value.first == CoordConsts::noCoord)
        {
            value.second = evaluateBoard(state.board);
        }
        
        if (isBetter(bestScore, value.second, state.currentPlayer)) {
            int bias = rand() % 10 + 50*(2 - difficulty);
            if ((rand() % 5) == 0) { bias = 0; }
            int multiplier = rand() % 2 == 0 ? 1 : - 1;
            bestScore = value.second * 0.9 + bias*multiplier;
            bestMove = { row, col };
        }
    }
    
    return { bestMove, bestScore };
}


//MARK: - Get Best Move
Coord getBestMove(const TicTacToeState &state, const int &difficulty)
{
    srand((unsigned int)time(NULL));
    return evalBestMove(state, difficulty).first;
}


Coord CoordConsts::noCoord = { -1, -1 };
