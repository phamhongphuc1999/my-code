#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

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

int main()
{
  Solution51 s = Solution51();
  vector<vector<string>> results = s.solveNQueens(4);
  for (vector<string> r1 : results)
  {
    for (string r : r1)
    {
      cout << r << endl;
    }
    cout << "------------------" << endl;
  }
}