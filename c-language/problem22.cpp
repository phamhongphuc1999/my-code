#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

void generate(vector<string> &result, string temp, char item, int openCounter, int closeCounter, int index, int len)
{
  if (temp.length() < len * 2)
  {
    if (index == 0)
    {
      temp = "(";
      if (len > 1)
        generate(result, temp, '(', 2, 0, 1, len);
      generate(result, temp, ')', 1, 1, 1, len);
    }
    else
    {
      temp += item;
      if (temp.length() == 2 * len)
        result.push_back(temp);
      else
      {
        if (openCounter > closeCounter)
          generate(result, temp, ')', openCounter, closeCounter + 1, index + 1, len);
        if (openCounter < len)
          generate(result, temp, '(', openCounter + 1, closeCounter, index + 1, len);
      }
    }
  }
}

/*https://leetcode.com/problems/generate-parentheses/description/*/
vector<string> generateParenthesis(int n)
{
  vector<string> result;
  generate(result, "", '1', 0, 0, 0, n);
  return result;
}

/*https://leetcode.com/problems/maximum-width-ramp/description/?envType=daily-question&envId=2024-10-10*/
int maxWidthRamp(vector<int> &nums)
{
  int size = nums.size();
  int rightMax[size];
  rightMax[size - 1] = nums[size - 1];
  for (int i = size - 2; i >= 0; i--)
  {
    rightMax[i] = max(rightMax[i + 1], nums[i]);
  }
  int left = 0;
  int right = 0;
  int _max = 0;
  while (right < size)
  {
    while (left < right && nums[left] > rightMax[right])
    {
      left++;
    }
    _max = max(_max, right - left);
    right++;
  }
  return _max;
}

// problem 1970
struct Node
{
  int row;
  int column;
  int direction; // 0-up, 1-down, 2-left, 3-right
};

class Solution
{
public:
  bool canCross(int row, int col, vector<vector<int>> &cells, int day)
  {
    vector<vector<int>> grid(row, vector<int>(col, 1));

    for (int i = 0; i <= day; i++)
    {
      grid[cells[i][0] - 1][cells[i][1] - 1] = 0;
    }

    queue<pair<int, int>> q;

    for (int c = 0; c < col; c++)
    {
      if (grid[0][c] == 1)
      {
        q.push({0, c});
        grid[0][c] = 2;
      }
    }

    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!q.empty())
    {
      auto [r, c] = q.front();
      q.pop();
      if (r == row - 1)
        return true;

      for (auto &d : dirs)
      {
        int nr = r + d[0], nc = c + d[1];
        if (nr >= 0 && nr < row && nc >= 0 && nc < col && grid[nr][nc] == 1)
        {
          grid[nr][nc] = 2;
          q.push({nr, nc});
        }
      }
    }

    return false;
  }

  bool dfs(vector<vector<int>> &lands, int row, int col, vector<Node> &result)
  {
    if (result.size() == 0)
    {
      for (int i = 0; i < col; i++)
      {
        if (lands[0][i] == 1)
        {
          result.push_back({0, i, 0});
          lands[0][i] = 2;
          if (dfs(lands, row, col, result))
            return true;
          result.pop_back();
          lands[0][i] = 1;
        }
      }
      return false;
    }
    else
    {
      Node temp = result.back();
      if (temp.row == row - 1)
        return true;
      if (temp.direction != 0 && temp.row > 0 && lands[temp.row - 1][temp.column] == 1)
      {
        result.push_back({temp.row - 1, temp.column, 1});
        lands[temp.row - 1][temp.column] = 2;
        if (dfs(lands, row, col, result))
          return true;
        result.pop_back();
        lands[temp.row - 1][temp.column] = 1;
      }
      if (temp.direction != 1 && temp.row < row - 1 && lands[temp.row + 1][temp.column] == 1)
      {
        result.push_back({temp.row + 1, temp.column, 0});
        lands[temp.row + 1][temp.column] = 2;
        if (dfs(lands, row, col, result))
          return true;
        result.pop_back();
        lands[temp.row + 1][temp.column] = 1;
      }
      if (temp.direction != 2 && temp.column > 0 && lands[temp.row][temp.column - 1] == 1)
      {
        result.push_back({temp.row, temp.column - 1, 3});
        lands[temp.row][temp.column - 1] = 2;
        if (dfs(lands, row, col, result))
          return true;
        result.pop_back();
        lands[temp.row][temp.column - 1] = 1;
      }
      if (temp.direction != 3 && temp.column < col - 1 && lands[temp.row][temp.column + 1] == 1)
      {
        result.push_back({temp.row, temp.column + 1, 2});
        lands[temp.row][temp.column + 1] = 2;
        if (dfs(lands, row, col, result))
          return true;
        result.pop_back();
        lands[temp.row][temp.column + 1] = 1;
      }
      return false;
    }
  }

  vector<Node> findPath(int row, int col, vector<vector<int>> &cells, int index)
  {
    vector<vector<int>> lands(row, vector<int>(col, 1));

    for (int i = 0; i <= index; i++)
    {
      int r = cells[i][0] - 1;
      int c = cells[i][1] - 1;
      lands[r][c] = 0;
    }
    vector<Node> result;
    dfs(lands, row, col, result);
    return result;
  }
  int latestDayToCross(int row, int col, vector<vector<int>> &cells)
  {
    int left = 0;
    int right = cells.size() - 1;
    int ans = -1;

    while (left <= right)
    {
      int mid = left + (right - left) / 2;

      if (canCross(row, col, cells, mid))
      {
        ans = mid;
        left = mid + 1;
      }
      else
      {
        right = mid - 1;
      }
    }
    return ans + 1;
  }
};

int main()
{
  vector<vector<int>> cells = {
      {1, 1}, {1, 2}, {2, 1}, {2, 2}};
  Solution s = Solution();
  int result = s.latestDayToCross(2, 2, cells);
  cout << "latest day: " << result << endl;

  // cout << "---------" << endl;
  //   for (int i = 0; i < row; i++)
  //   {
  //     for (int j = 0; j < col; j++)
  //     {
  //       cout << lands[i][j] << ", ";
  //     }
  //     cout << endl;
  //   }
  //   cout << "---------" << endl;
}