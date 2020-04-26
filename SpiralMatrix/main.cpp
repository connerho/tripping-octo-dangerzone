#include "SpiralMatrix.h"

int main()
{
  std::vector<std::vector<int>> matrix;
  std::vector<int> row1 = {1, 2, 3, 10};
  std::vector<int> row2 = {4, 5, 6, 11};
  std::vector<int> row3 = {7, 8, 9, 12};
  matrix.push_back(row1);
  matrix.push_back(row2);
  matrix.push_back(row3);

  SpiralMatrix mySpiral(matrix);
  mySpiral.printMatrix();

  return 0;
}