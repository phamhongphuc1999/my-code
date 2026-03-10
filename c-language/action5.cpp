#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
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

struct Node
{
  vector<int> arr;
  int latestIndex;
  int total;
};

// https://leetcode.com/problems/combination-sum-ii/
vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
{
  sort(candidates.begin(), candidates.end());
  vector<vector<int>> result;
  stack<Node> st;
  int preValue = -1;
  for (int i = 0; i < candidates.size(); i++)
  {
    if (preValue != candidates.at(i))
      st.push({{candidates.at(i)}, i, candidates.at(i)});
    preValue = candidates.at(i);
  }
  while (st.size() > 0)
  {
    Node cur = st.top();
    st.pop();
    if (cur.total == target)
    {
      vector<int> curArr = cur.arr;
      result.push_back(curArr);
    }
    else if (cur.total < target)
    {
      vector<int> _arr = cur.arr;
      int preValue = -1;
      for (int i = cur.latestIndex + 1; i < candidates.size(); i++)
      {
        if (preValue != candidates.at(i))
        {
          vector<int> curArr = cur.arr;
          curArr.push_back(candidates.at(i));
          int total = cur.total + candidates.at(i);
          if (total <= target)
            st.push({curArr, i, total});
          else
            break;
        }
        preValue = candidates.at(i);
      }
    }
  }
  return result;
}

// 18. 4Sum
vector<vector<int>> fourSum(vector<int> &nums, int target)
{
  vector<vector<int>> result;
  int n = nums.size();
  if (n < 4)
    return result;

  sort(nums.begin(), nums.end());

  for (int i = 0; i < n - 3; i++)
  {
    if (i > 0 && nums[i] == nums[i - 1])
      continue; // skip dup

    for (int j = i + 1; j < n - 2; j++)
    {
      if (j > i + 1 && nums[j] == nums[j - 1])
        continue; // skip dup

      long long rem = (long long)target - nums[i] - nums[j];
      int l = j + 1, r = n - 1;

      while (l < r)
      {
        long long sum = nums[l] + nums[r];
        if (sum == rem)
        {
          result.push_back({nums[i], nums[j], nums[l], nums[r]});

          // skip duplicates
          while (l < r && nums[l] == nums[l + 1])
            l++;
          while (l < r && nums[r] == nums[r - 1])
            r--;

          l++;
          r--;
        }
        else if (sum < rem)
        {
          l++;
        }
        else
        {
          r--;
        }
      }
    }
  }
  return result;
}

// 1925. Count Square Sum Triples
int countTriples(int n)
{
  int __result = 0;
  for (int i = 1; i <= n; i++)
  {
    for (int j = i + 1; j <= n; j++)
    {
      int power = i * i + j * j;
      double result = sqrt(power);
      int _result = ceil(result);
      if (_result > n)
        break;
      if (_result * _result == power)
        __result += 2;
    }
  }
  return __result;
}

int countNegatives(vector<vector<int>> &grid)
{
  int m = grid.size();
  int n = grid.at(0).size();
  int row = m - 1;
  int col = 0;
  int count = 0;
  while (row >= 0 && col < n)
  {
    if (grid.at(row).at(col) < 0)
    {
      count += n - col;
      row -= 1;
    }
    else
      col += 1;
  }
  return count;
}

int32_t clampToInt32(long long x)
{
  const long long INT32_MIN_LL = -2147483648LL;
  const long long INT32_MAX_LL = 2147483647LL;

  if (x < INT32_MIN_LL)
    return INT32_MIN_LL;
  if (x > INT32_MAX_LL)
    return INT32_MAX_LL;
  return static_cast<int32_t>(x);
}

// 8. String to Integer (atoi)
int myAtoi(string s)
{
  int count__ = 0;
  while (count__ < s.length())
  {
    if (s[count__] == ' ')
      count__++;
    else
      break;
  }
  long long result = 0;
  int count = 0;
  int sign = 1;

  while (count + count__ < s.length())
  {
    char _c = s.at(count + count__);
    if (count == 0)
    {
      if (_c == '-')
        sign = -1;
      else if (_c != '+')
      {
        if (_c >= '0' && _c <= '9')
        {
          result = result * 10 + (_c - '0');
        }
        else
          break;
      }
    }
    else if (_c >= '0' && _c <= '9')
    {
      result = result * 10 + (_c - '0');
      int _check__ = clampToInt32(result);
      if (_check__ != result)
        if (sign == 1)
          return 2147483647;
        else
          return -2147483648;
    }
    else
      break;
    count++;
  }
  return result * sign;
}

// https://leetcode.com/problems/max-area-of-island/
int maxAreaOfIsland(vector<vector<int>> &grid)
{
  int len = grid.size();
  if (len == 0)
    return 0;
  int rowLen = grid.at(0).size();
  if (rowLen == 0)
    return 0;
  vector<vector<int>> visited(len, vector<int>(rowLen, 0));
  int result = 0;
  for (int i = 0; i < len; i++)
  {
    for (int j = 0; j < rowLen; j++)
    {
      if (visited[i][j] == 0)
      {
        visited[i][j] = 1;
        if (grid[i][j] > 0)
        {
          queue<pair<int, int>> temp;
          temp.push({i, j});
          int _tempMax = 0;
          while (temp.size() > 0)
          {
            pair<int, int> _pair = temp.front();
            temp.pop();
            _tempMax += 1;
            int first = _pair.first;
            int second = _pair.second;
            if (second < rowLen - 1 && visited[first][second + 1] == 0)
            {
              visited[first][second + 1] = 1;
              if (grid[first][second + 1] > 0)
                temp.push({first, second + 1});
            }
            if (first < len - 1 && visited[first + 1][second] == 0)
            {
              visited[first + 1][second] = 1;
              if (grid[first + 1][second] > 0)
                temp.push({first + 1, second});
            }
            if (first >= 1 && visited[first - 1][second] == 0)
            {
              visited[first - 1][second] = 1;
              if (grid[first - 1][second] > 0)
                temp.push({first - 1, second});
            }
            if (second >= 1 && visited[first][second - 1] == 0)
            {
              visited[first][second - 1] = 1;
              if (grid[first][second - 1] > 0)
                temp.push({first, second - 1});
            }
          }
          result = max(result, _tempMax);
        }
      }
    }
  }
  return result;
}

// problem 51
class Solution51
{
public:
  vector<vector<string>> solveNQueens(int n)
  {
    vector<string> results;
    queue<string> qq;
    for (int i = 0; i < n; i++)
    {
      qq.push(to_string(i));
    }
    while (qq.size() > 0)
    {
      string value = qq.front();
      if (value.length() == n)
      {
        qq.pop();
        results.push_back(value);
      }
      else
      {
        qq.pop();
        int temp[n];
        memset(temp, 0, sizeof(temp));
        for (int i = 0; i < value.length(); i++)
        {
          int offset = value.length() - i;
          int index = value[i] - '0';
          temp[index] = 1;
          if (index >= offset)
            temp[index - offset] = 1;
          if (index < n - offset)
            temp[index + offset] = 1;
        }
        for (int i = 0; i < n; i++)
        {
          if (temp[i] == 0)
            qq.push(value + to_string(i));
        }
      }
    }
    vector<vector<string>> realResult;
    for (string lll : results)
    {
      vector<string> _rrrr;
      for (int i = 0; i < n; i++)
      {

        int index = lll[i] - '0';
        string prefix(index, '.');
        string suffix(n - 1 - index, '.');
        _rrrr.push_back(prefix + 'Q' + suffix);
      }
      realResult.push_back(_rrrr);
    }
    return realResult;
  }
};
