#include "Minesweeper.h"
#include <iostream>

void Game::Tile::incrementChar()
{
    switch(dispChar)
    {
        default:
        case ' ':
        dispChar = '1';
        break;

        case '1':
        dispChar = '2';
        break;

        case '2':
        dispChar = '3';
        break;

        case '3':
        dispChar = '4';
        break;

        case '4':
        dispChar = '5';
        break;

        case '5':
        dispChar = '6';
        break;

        case '6':
        dispChar = '7';
        break;

        case '7':
        dispChar = '8';
        break;

        case 'B':
        break;
    }
}

Game::Minesweeper::Minesweeper(int xDim, int yDim, std::vector<Game::Coordinate> bombs)
{
    for(int i = 0; i < yDim; ++i)
    {
        std::vector<Game::Tile> row;

        for(int j = 0; j < xDim; ++j)
        {
            row.push_back(Tile(j, i, ' '));
        }

        gameBoard.push_back(row);
    }

    initializeBoard(bombs);
}

Game::Minesweeper::~Minesweeper()
{

}

void Game::Minesweeper::printBoard()
{
    for(int i = 0; i < gameBoard.size(); ++i)
    {
        for(int j = 0; j < gameBoard[0].size(); ++j)
        {
            std::cout << "| " << gameBoard[i][j].dispChar << " ";
        }

        std::cout << "|\n";
        std::cout << "--------------------------------------\n";
    }
}

void Game::Minesweeper::initializeBoard(std::vector<Game::Coordinate> bombs)
{
    for(int i = 0; i < bombs.size(); ++i)
    {
        gameBoard[bombs[i].ycoord][bombs[i].xcoord].setChar('B');

        for(int j = bombs[i].xcoord - 1; j <= bombs[i].xcoord + 1; ++j)
        {
            for(int k = bombs[i].ycoord - 1; k <= bombs[i].ycoord + 1; ++k)
            {
                if(j < 0) continue;
                if(j >= gameBoard[0].size()) continue;
                if(k < 0) continue;
                if(k >= gameBoard.size()) continue;
                if(gameBoard[k][j].dispChar == 'B') continue;

                gameBoard[k][j].incrementChar();
            }
        }
    }
}