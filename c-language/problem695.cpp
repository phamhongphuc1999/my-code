#include <iostream>
#include <vector>
#include <queue>

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

int main()
{
}