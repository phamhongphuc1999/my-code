#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

/*https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/description/*/
int smallestChair(vector<vector<int>> &times, int targetFriend)
{
  vector<int> visitTimes;
  vector<vector<int>> leaveTimes;
  int counter = 0;
  int targetVisitTime = -1;
  for (vector<int> time : times)
  {
    visitTimes.push_back(time[0]);
    leaveTimes.push_back(time);
    if (counter == targetFriend)
      targetVisitTime = time[0];
    counter++;
  }
  unordered_map<int, int> umap;
  priority_queue<int, vector<int>, greater<int>> chairs;
  sort(visitTimes.begin(), visitTimes.end());
  sort(leaveTimes.begin(), leaveTimes.end(), [](vector<int> &item1, vector<int> &item2)
       { return item1[1] < item2[1]; });
  int visitCounter = 0;
  int leaveCounter = 0;
  chairs.push(0);
  while (targetVisitTime >= leaveTimes[leaveCounter][1] || targetVisitTime > visitTimes[visitCounter])
  {
    int _visit = visitTimes[visitCounter];
    int _leave = leaveTimes[leaveCounter][1];
    if (_visit < _leave)
    {
      visitCounter++;
      int chair = chairs.top();
      chairs.pop();
      if (chairs.empty())
        chairs.push(chair + 1);
      umap[_visit] = chair;
    }
    else
    {
      int chair = umap[leaveTimes[leaveCounter][0]];
      chairs.push(chair);
      leaveCounter++;
    }
  }
  return chairs.top();
}

// problem 1411
class Solution1411
{
  int mod = 1000000007;

public:
  int numOfWays(int n)
  {
    if (n == 1)
      return 12;
    long long fivePieces = 6;
    long long fourPieces = 6;
    for (int i = 2; i <= n; i++)
    {
      long long tempFivePieces = fivePieces * 3 + fourPieces * 2;
      long long tempFourPieces = fivePieces * 2 + fourPieces * 2;
      fivePieces = tempFivePieces > mod ? tempFivePieces % mod : tempFivePieces;
      fourPieces = tempFourPieces > mod ? tempFourPieces % mod : tempFourPieces;
    }
    return (fivePieces + fourPieces) % mod;
  }
};

bool exists(int mask, int index)
{
  return (mask >> index) & 1;
}

int add(int mask, int x)
{
  int result = (1 << x) | mask;
  return result;
}

void subtract(int &mask, int x)
{
  mask &= ~(1 << x);
}

struct Problem1942
{
  vector<int> indices;
  int lastIndex;
};

Problem1942 getSetBits(int mask, vector<int> &nums)
{
  vector<int> indices;
  int index = 0;
  int lastIndex = 0;

  while (mask > 0)
  {
    if (mask & 1)
    {
      indices.push_back(nums[index]);
      lastIndex = index;
    }
    mask >>= 1;
    index++;
  }
  return Problem1942{indices, lastIndex};
}
class Solution78
{
public:
  vector<vector<int>> subsets(vector<int> &nums)
  {
    vector<vector<int>> results;
    results.push_back({});
    queue<int> qu;
    for (int i = 0; i < nums.size(); i++)
    {
      int _zero = 0;
      qu.push(add(0, i));
    }
    while (qu.size() > 0)
    {
      int _value = qu.front();
      Problem1942 _temp = getSetBits(_value, nums);
      results.push_back(_temp.indices);
      qu.pop();
      for (int i = _temp.lastIndex + 1; i < nums.size(); i++)
      {
        int __value = add(_value, i);
        qu.push(__value);
      }
    }
    return results;
  }
};

// problem 1942
vector<vector<int>> subsets(vector<int> &nums)
{
  int n = nums.size();
  vector<vector<int>> res;
  res.reserve(1 << n);

  for (int mask = 0; mask < (1 << n); mask++)
  {
    vector<int> subset;
    for (int i = 0; i < n; i++)
    {
      if (mask & (1 << i))
        subset.push_back(nums[i]);
    }
    res.push_back(subset);
  }
  return res;
}

// problem 79
bool exist(vector<vector<char>> &board, string word)
{
  int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  int row = board.size();
  int col = board[0].size();
  vector<vector<int>> grid(row, vector<int>(col, 1));
  queue<tuple<int, int, int>> q;
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      if (board[i][j] == word[0])
      {
        q.push({i, j, 0});
        grid[i][j] = 0;
      }
    }
  }
  while (!q.empty())
  {
    auto [_row, _col, _index] = q.front();
    q.pop();
    if (_index == word.length() - 1)
      return true;
    for (auto [i, j] : dirs)
    {
      int newRow = _row + i;
      int newCol = _col + j;
      if (newRow >= 0 && newRow < row && newCol >= 0 && newCol < col && grid[newRow][newCol] == 1)
      {
        if (word[_index + 1] == board[newRow][newCol])
        {
          q.push({newRow, newCol, _index + 1});
          grid[newRow][newCol] = 0;
        }
      }
    }
  }
  return false;
}

int main()
{
  vector<vector<char>> board = {{'A', 'B', 'C', 'E'},
                                {'S', 'F', 'C', 'S'},
                                {'A', 'D', 'E', 'E'}};
  cout << exist(board, "ABCB") << endl;
}
