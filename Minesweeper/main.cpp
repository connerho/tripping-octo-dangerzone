#include "Minesweeper.h"

int main()
{
    std::vector<Game::Coordinate> bombList;
    bombList.push_back(Game::Coordinate(0, 0));
    bombList.push_back(Game::Coordinate(1, 1));
    bombList.push_back(Game::Coordinate(1, 2));

    Game::Minesweeper myGame(3,3,bombList);
    myGame.printBoard();

    return 0;
}