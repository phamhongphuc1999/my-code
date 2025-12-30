#include <bits/stdc++.h>
using namespace std;

// problem 756
class Solution
{
public:
  int T[7][7];
  unordered_set<long long> seen;

  bool pyramidTransition(string bottom, vector<string> &allowed)
  {
    memset(T, 0, sizeof(T));

    for (const string &a : allowed)
    {
      int x = a[0] - 'A';
      int y = a[1] - 'A';
      int z = a[2] - 'A';
      T[x][y] |= (1 << z);
    }

    int N = bottom.size();
    vector<vector<int>> A(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
    {
      A[N - 1][i] = bottom[i] - 'A';
    }

    seen.clear();

    return solve(A, 0LL, N - 1, 0);
  }

private:
  bool solve(vector<vector<int>> &A, long long R, int N, int i)
  {
    if (N == 1 && i == 1)
    {
      return true;
    }

    if (i == N)
    {
      if (seen.count(R))
        return false;
      seen.insert(R);
      return solve(A, 0LL, N - 1, 0);
    }

    int w = T[A[N][i]][A[N][i + 1]];

    if (w == 0)
      return false;

    for (int b = 0; b < 7; b++)
    {
      if ((w >> b) & 1)
      {
        A[N - 1][i] = b;

        if (solve(A, R * 8 + (b + 1), N, i + 1))
          return true;
      }
    }

    return false;
  }
};

class Solution840
{
public:
  // problem 840
  int numMagicSquaresInside(vector<vector<int>> &grid)
  {
    int rows = grid.size();
    if (rows < 3)
      return 0;
    int columns = grid[0].size();
    if (columns < 3)
      return 0;
    int checkRow[rows][columns - 2];
    memset(checkRow, 0, sizeof(checkRow));
    int checkColumn[rows - 2][columns];
    memset(checkColumn, 0, sizeof(checkColumn));
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < columns - 2; j++)
      {
        int item1 = grid[i][j];
        int item2 = grid[i][j + 1];
        int item3 = grid[i][j + 2];
        if (item1 + item2 + item3 == 15)
          checkRow[i][j] = 1;
      }
    }
    for (int j = 0; j < columns; j++)
    {
      for (int i = 0; i < rows - 2; i++)
      {
        int item1 = grid[i][j];
        int item2 = grid[i + 1][j];
        int item3 = grid[i + 2][j];
        if (item1 + item2 + item3 == 15)
          checkColumn[i][j] = 1;
      }
    }
    int result = 0;
    for (int i = 0; i < rows - 2; i++)
    {
      for (int j = 0; j < columns - 2; j++)
      {
        if (checkRow[i][j] == 1 && checkRow[i + 1][j] == 1 && checkRow[i + 2][j] == 1 && checkColumn[i][j] == 1 && checkColumn[i][j + 1] == 1 && checkColumn[i][j + 2] == 1)
        {
          int total1 = grid[i][j] + grid[i + 1][j + 1] + grid[i + 2][j + 2];
          int total2 = grid[i][j + 2] + grid[i + 1][j + 1] + grid[i + 2][j];
          if (total1 == total2 && total2 == 15)
          {
            int _check = 0;
            _check |= 1 << grid[i][j];
            _check |= 1 << grid[i][j + 1];
            _check |= 1 << grid[i][j + 2];
            _check |= 1 << grid[i + 1][j];
            _check |= 1 << grid[i + 1][j + 1];
            _check |= 1 << grid[i + 1][j + 2];
            _check |= 1 << grid[i + 2][j];
            _check |= 1 << grid[i + 2][j + 1];
            _check |= 1 << grid[i + 2][j + 2];
            if (_check == 1022)
              result += 1;
          }
        }
      }
    }
    return result;
  }
};

int main()
{
  Solution840 s = Solution840();
  vector<vector<int>> a = {{4, 3, 8, 4}, {9, 5, 1, 9}, {2, 7, 6, 2}};
  int result = s.numMagicSquaresInside(a);
  cout << result << endl;
}
