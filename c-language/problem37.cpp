#include <iostream>
#include <vector>
#include <queue>
#include "header.h"

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

class Solution116
{
public:
  NextNode *connect(NextNode *root)
  {
    if (root == NULL)
      return NULL;
    queue<NextNode *> q;
    q.push(root);
    while (!q.empty())
    {
      int size = q.size();
      for (int i = 0; i < size - 1; i++)
      {
        NextNode *top = q.front();
        q.pop();
        top->next = q.front();
        if (top->left != NULL)
          q.push(top->left);
        if (top->right != NULL)
          q.push(top->right);
      }
      NextNode *top = q.front();
      q.pop();
      top->next = NULL;
      if (top->left != NULL)
        q.push(top->left);
      if (top->right != NULL)
        q.push(top->right);
    }
    return root;
  }
};

class Solution98
{
public:
  bool lessThanDfs(TreeNode *root, int _max)
  {
    if (root == NULL)
      return true;
    if (root->val >= _max)
      return false;
    bool leftCheck = lessThanDfs(root->left, root->val);
    bool rightCheck = rangeDfs(root->right, root->val, _max);
    return leftCheck && rightCheck;
  }

  bool greaterThanDfs(TreeNode *root, int _min)
  {
    if (root == NULL)
      return true;
    if (root->val <= _min)
      return false;
    bool leftCheck = rangeDfs(root->left, _min, root->val);
    bool rightCheck = greaterThanDfs(root->right, root->val);
    return leftCheck && rightCheck;
  }

  bool rangeDfs(TreeNode *root, int _min, int _max)
  {
    if (root == NULL)
      return true;
    if (root->val <= _min || root->val >= _max)
      return false;
    bool leftCheck = rangeDfs(root->left, _min, root->val);
    bool rightCheck = rangeDfs(root->right, root->val, _max);
    return leftCheck && rightCheck;
  }

  bool isValidBST(TreeNode *root)
  {
    bool leftCheck = lessThanDfs(root->left, root->val);
    bool rightCheck = greaterThanDfs(root->right, root->val);
    return leftCheck && rightCheck;
  }
};