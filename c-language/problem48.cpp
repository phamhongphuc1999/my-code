#include <iostream>
#include <vector>

using namespace std;

// https://leetcode.com/problems/rotate-image/
void rotate(vector<vector<int>> &matrix)
{
  vector<vector<int>> cloneMatrix(matrix);
  int len = matrix.size();
  for (int row = 0; row < len; row++)
  {
    for (int column = 0; column < len; column++)
    {
      int newRow = column;
      int newColumn = len - 1 - row;
      matrix[newRow][newColumn] = cloneMatrix[row][column];
    }
  }
}