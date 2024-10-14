#include <iostream>
#include <vector>

using namespace std;

bool is_possible(std::vector<std::vector<int>> &board, int row, int col, int val)
{
  for (int i = 0; i < 9; i++)
  {
    if (board[i][col] == val)
      return false;
  }
  for (int i = 0; i < 9; i++)
  {
    if (board[row][i] == val)
      return false;
  }
  int startRow = 3 * (row / 3);
  int startCol = 3 * (col / 3);

  for (int i = startRow; i < startRow + 3; i++)
  {
    for (int j = startCol; j < startCol + 3; j++)
    {
      if (board[i][j] == val)
        return false;
    }
  }
  return true;
}

bool solve(std::vector<std::vector<int>> &board, int row, int col)
{

  if (col == 9)
  {
    if (row == 8)
      return true;
    col = 0;
    row++;
  }

  if (board[row][col] != 0)
    return solve(board, row, col + 1);

  for (int x = 1; x <= 9; x++)
  {
    if (is_possible(board, row, col, x))
    {
      board[row][col] = x;
      if (solve(board, row, col + 1))
        return true;
    }
    board[row][col] = 0;
  }
  return false;
}

void solveSudoku(vector<vector<char>> &board)
{
  vector<vector<int>> data;
  for (int i = 0; i < 9; i++)
  {
    vector<int> temp;
    for (int j = 0; j < 9; j++)
    {
      if (board[i][j] == '.')
        temp.push_back(0);
      else
        temp.push_back(board[i][j] - '0');
    }
    data.push_back(temp);
  }
  solve(data, 0, 0);
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      board[i][j] = '0' + data[i][j];
    }
  }
}

int main()
{
  vector<char> row1{'5', '3', '.', '.', '7', '.', '.', '.', '.'};
  vector<char> row2{'6', '.', '.', '1', '9', '5', '.', '.', '.'};
  vector<char> row3{'.', '9', '8', '.', '.', '.', '.', '6', '.'};
  vector<char> row4{'8', '.', '.', '.', '6', '.', '.', '.', '3'};
  vector<char> row5{'4', '.', '.', '8', '.', '3', '.', '.', '1'};
  vector<char> row6{'7', '.', '.', '.', '2', '.', '.', '.', '6'};
  vector<char> row7{'.', '6', '.', '.', '.', '.', '2', '8', '.'};
  vector<char> row8{'.', '.', '.', '4', '1', '9', '.', '.', '5'};
  vector<char> row9{'.', '.', '.', '.', '8', '.', '.', '7', '9'};
  vector<vector<char>> board{row1, row2, row3, row4, row5, row6, row7, row8, row9};
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl
       << endl;
  solveSudoku(board);
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}