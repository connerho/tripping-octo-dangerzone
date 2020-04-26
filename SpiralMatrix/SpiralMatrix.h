#include <vector>
#include <iostream>

struct Coordinate
{
  int x;
  int y;
};

enum Direction
{
  RIGHT,
  DOWN,
  LEFT,
  UP
};

class SpiralMatrix
{
public:
  SpiralMatrix(std::vector<std::vector<int>>& input) : matrix(input)
  {
    findCenter();
  }

  void printMatrix()
  {
    bool done = false;
    std::vector<int> printVector;
    Coordinate currentCoord = center;
    Direction dir = RIGHT;
    int bound = 1;
    int step = 0;

    while(!done)
    {
      printVector.push_back(matrix[currentCoord.y][currentCoord.x]);
      update(currentCoord, dir, bound, step, done);
    }

    for(int i = 0; i < printVector.size(); ++i)
    {
      std::cout << printVector[i] << " ";
    }
  }

  ~SpiralMatrix() {}

private:
  std::vector<std::vector<int>> matrix;
  Coordinate center;

  void findCenter()
  {
    center.x = (matrix[0].size() - 1) / 2;
    center.y = (matrix.size() - 1) / 2;
  }

  void update(Coordinate& myCoord, Direction& dir, int& bound, int& step, bool& done)
  {
    switch (dir)
    {
    default:
    case RIGHT:
      myCoord.x++;
      break;

    case DOWN:
      myCoord.y++;
      break;

    case LEFT:
      myCoord.x--;
      break;

    case UP:
      myCoord.y--;
      break;
    }

    step++;

    // Check for done conditions
    if(myCoord.x < 0 || myCoord.x >= matrix[0].size() || myCoord.y < 0 || myCoord.y >= matrix.size())
    {
      done = true;
      return;
    }

    // Check to see if we need to change direction
    if(step == bound) updateDirAndBound(dir, bound, step);
  }

  void updateDirAndBound(Direction& dir, int& bound, int& step)
  {
    switch(dir)
    {
      default:
      case RIGHT:
        dir = DOWN;
        step = 0;
        break;

      case DOWN:
        dir = LEFT;
        bound++;
        step = 0;
        break;

      case LEFT:
        dir = UP;
        step = 0;
        break;

      case UP:
        dir = RIGHT;
        bound++;
        step = 0;
        break;
    }
  }

};