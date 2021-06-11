//
//  minimax.cpp
//  WASM
//
//  Created by Jakub Charvat on 10.06.2021.
//

#include "minimax.hpp"

#include <vector>

#include "sharedFunctions.hpp"

#define WIN_SCORE 100
#define TWO_IN_ROW_SCORE 10


// Cross tries to maximise score, naught tries to minimise it

int scoreForLine(Player a, Player b, Player c)
{
    if (a == b && b == c)
    {
        return a == Cross ? WIN_SCORE : -WIN_SCORE;
    }
    
    if (a == b || b == c)
    {
        return b == Cross ? TWO_IN_ROW_SCORE : -TWO_IN_ROW_SCORE;
    }
    
    return 0;
}


//MARK: - Evaluate Board
int evaluateBoard(const Board &board)
{
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


std::pair<Coord, int> evalBestMove(const TicTacToeState &state)
{
    std::vector<Coord> possibleMoves = generateMoves(state.board);
    
    if (possibleMoves.empty())
    {
        return { noCoord, 0 };
    }
    
    Coord bestMove = noCoord;
    int bestScore = state.currentPlayer == Cross ? INT_MIN : INT_MAX;
    
    for (auto move: possibleMoves)
    {
        int row = move.first, col = move.second;
        WinDirection dir = checkWin(state.board, state.currentPlayer, row, col);
        if (dir != NoDirection)
        {
            int score = evaluateBoard(state.board);
            if (isBetter(bestScore, score, state.currentPlayer))
            {
                bestScore = score;
                bestMove = move;
            }
            continue;
        }
        
        TicTacToeState stateCopy = state;
        play(&stateCopy, row, col);
        std::pair<Coord, int> value = evalBestMove(stateCopy);
        if (isBetter(bestScore, value.second, state.currentPlayer)) {
            bestScore = value.second;
            bestMove = value.first;
        }
    }
    
    return { { 0, 0 }, 0 };
}


//MARK: - Get Best Move
Coord getBestMove(const TicTacToeState &state)
{
    return evalBestMove(state).first;
}
