
#include <vector>

namespace Game
{

struct Coordinate
{
    int xcoord;
    int ycoord;

    Coordinate(int x, int y) : xcoord(x), ycoord(y) {}
};

struct Tile
{
    Coordinate myCoord;
    bool visible;
    char dispChar;

    Tile(int x, int y, char c) : myCoord(x,y), visible(false), dispChar(c) {}
    void setChar(char input) { dispChar = input; }
    void incrementChar();
};

class Minesweeper
{
public:

    Minesweeper(int xDim, int yDim, std::vector<Coordinate> bombs);
    virtual ~Minesweeper();

    void printBoard();

private:

    void initializeBoard(std::vector<Coordinate> bombs);
    std::vector<std::vector<Tile>> gameBoard;
};

}