#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <stack>
#include <string>
#include "header.h"

using namespace std;

vector<int> getFinalState(vector<int> &nums, int k, int multiplier)
{
  priority_queue<int, vector<int>, greater<int>> pq;
  map<int, priority_queue<int, vector<int>, greater<int>>> hash;
  int counter = 0;
  for (int num : nums)
  {
    pq.push(num);
    map<int, priority_queue<int, vector<int>, greater<int>>>::iterator temp = hash.find(num);
    if (hash.find(num) != hash.end())
      hash[num].push(counter);
    else
    {
      priority_queue<int, vector<int>, greater<int>> _temp;
      _temp.push(counter);
      hash.insert({num, _temp});
    }
    counter++;
  }
  for (int i = 0; i < k; i++)
  {
    int minValue = pq.top();
    pq.pop();
    int newValue = minValue * multiplier;
    int index = hash[minValue].top();
    hash[minValue].pop();
    nums[index] = newValue;

    pq.push(newValue);
    map<int, priority_queue<int, vector<int>, greater<int>>>::iterator check = hash.find(newValue);
    if (check != hash.end())
    {
      hash[newValue].push(index);
    }
    else
    {
      priority_queue<int, vector<int>, greater<int>> _new;
      _new.push(index);
      hash.insert({newValue, _new});
    }
  }
  return nums;
}

bool canThreePartsEqualSum(vector<int> &arr)
{
  int total = 0;
  for (int i : arr)
    total += i;
  if (total % 3 != 0)
    return false;
  int targetTotal = total / 3;
  int remaining = targetTotal;
  int okCounter = 0;
  bool isFinalRound = false;
  int finalRound = targetTotal;
  for (int i : arr)
  {
    if (okCounter < 2)
    {
      remaining -= i;
      if (remaining == 0)
      {
        okCounter++;
        remaining = targetTotal;
      }
    }
    else
    {
      finalRound -= i;
      isFinalRound = true;
    }
  }
  return finalRound == 0 && okCounter == 2 && isFinalRound;
}

// 3432. Count Partitions with Even Sum Difference
int countPartitions(vector<int> &nums)
{
  int total = 0;
  for (int item : nums)
  {
    total += item;
  }
  int firstTotal = 0;
  int result = 0;
  for (int i = 0; i < nums.size() - 1; i++)
  {
    firstTotal += nums.at(i);
    if ((2 * firstTotal - total) % 2 == 0)
      result++;
  }
  return result;
}

string phoneNumbers[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

struct CombinationNode
{
  string arr;
  int prevIndex;
};

// 17. Letter Combinations of a Phone Number
vector<string> letterCombinations(string digits)
{
  vector<string> result;
  stack<CombinationNode> st;
  int index = digits[0] - '0' - 2;
  for (char _char : phoneNumbers[index])
  {
    st.push({string("") + _char, 0});
  }
  while (st.size() > 0)
  {
    CombinationNode item = st.top();
    int currentIndex = item.prevIndex + 1;
    if (currentIndex == digits.length())
    {
      string _value = item.arr;
      result.push_back(_value);
      st.pop();
    }
    else
    {
      string _value = item.arr;
      int index = digits[currentIndex] - '0' - 2;
      st.pop();
      for (char _char : phoneNumbers[index])
      {
        st.push({_value + _char, currentIndex});
      }
    }
  }

  return result;
}

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

int countCollisions(string directions)
{
  stack<char> st;
  int result = 0;
  for (char c : directions)
  {
    if (st.size() == 0)
    {
      if (c != 'L')
        st.push(c);
    }
    else
    {
      char pre = st.top();
      if ((pre == 'S' || pre == 'L') && c == 'L')
      {
        result += 1;
        st.push(c);
      }
      else if (pre == 'R' && c == 'L')
      {
        result += 2;
        st.pop();
        while (st.size() > 0 && st.top() == 'R')
        {
          result += 1;
          st.pop();
        }
        st.push(c);
      }
      else if (c == 'R')
        st.push(c);
      else
      {
        while (st.size() > 0 && st.top() == 'R')
        {
          result += 1;
          st.pop();
        }
        st.push(c);
      }
    }
  }
  return result;
}

bool canChange(string start, string target)
{
  int startLength = start.size();
  // Pointer for start string and target string
  int startIndex = 0, targetIndex = 0;

  while (startIndex < startLength || targetIndex < startLength)
  {
    // Skip underscores in start
    while (startIndex < startLength && start[startIndex] == '_')
    {
      startIndex++;
    }
    // Skip underscores in target
    while (targetIndex < startLength && target[targetIndex] == '_')
    {
      targetIndex++;
    }
    // If one string is exhausted, both should be exhausted
    if (startIndex == startLength || targetIndex == startLength)
    {
      return startIndex == startLength && targetIndex == startLength;
    }

    // Check if the pieces match and follow movement rules
    if (start[startIndex] != target[targetIndex] ||
        (start[startIndex] == 'L' && startIndex < targetIndex) ||
        (start[startIndex] == 'R' && startIndex > targetIndex))
      return false;

    startIndex++;
    targetIndex++;
  }

  // If all conditions are satisfied, return true
  return true;
}

int maxCount(vector<int> &banned, int n, int maxSum)
{
  sort(banned.begin(), banned.end());
  int num = 1;
  int index = 0;
  int remainingSum = maxSum;
  int counter = 0;
  int _len = banned.size();
  vector<int> result;
  while (num <= n)
  {
    while (banned[index] <= num && index < _len && num <= n)
    {
      if (num == banned[index])
      {
        num = banned[index] + 1;
        index++;
      }
      else
        index++;
    }
    if (remainingSum >= num && num <= n)
    {
      remainingSum -= num;
      result.push_back(num);
      counter++;
      num++;
    }
    else
      break;
  }
  return counter;
}

class Solution47
{
public:
  vector<vector<int>> permuteUnique(vector<int> &nums)
  {
    vector<vector<int>> results;
    unordered_map<int, int> counters;
    for (int num : nums)
      counters[num]++;
    vector<int> temp;
    backtracking(temp, results, counters, 0, nums.size());
    return results;
  }

  void backtracking(vector<int> temp, vector<vector<int>> &results, unordered_map<int, int> &counters, int index, int len)
  {
    if (index == len)
      results.push_back(temp);
    else
    {

      for (auto &item : counters)
      {
        if (item.second > 0)
        {
          temp.push_back(item.first);
          item.second -= 1;
          backtracking(temp, results, counters, index + 1, len);
          temp.pop_back();
          item.second += 1;
        }
      }
    }
  }
};

class Solution47_v2
{
public:
  vector<vector<int>> permuteUnique(vector<int> &nums)
  {
    vector<vector<int>> results;
    int counters[21];
    memset(counters, 0, sizeof(counters));
    for (int num : nums)
      counters[num + 10]++;
    vector<int> temp;
    backtracking(temp, results, counters, 0, nums.size());
    return results;
  }

  void backtracking(vector<int> temp, vector<vector<int>> &results, int counters[21], int index, int len)
  {
    if (index == len)
      results.push_back(temp);
    else
    {
      for (int i = 0; i < 21; i++)
      {
        if (counters[i] > 0)
        {
          temp.push_back(i - 10);
          counters[i]--;
          backtracking(temp, results, counters, index + 1, len);
          temp.pop_back();
          counters[i]++;
        }
      }
    }
  }
};

class Solution77
{
public:
  vector<vector<int>> combine(int n, int k)
  {
    vector<vector<int>> results;
    int counters[n];
    memset(counters, 1, sizeof(counters));
    vector<int> temp;
    backtracking(results, temp, counters, 0, k, n);
    return results;
  }

  void backtracking(vector<vector<int>> &results, vector<int> &temp, int counters[], int index, int k, int n)
  {
    if (k == index)
    {
      results.push_back(temp);
    }
    else
    {
      for (int i = 1; i <= n; i++)
      {
        bool canRun = false;
        int _size = temp.size();
        if (_size == 0)
        {
          temp.push_back(i);
          canRun = true;
          counters[i - 1]--;
        }
        else
        {
          if (i + index - k <= n && i > temp[_size - 1])
          {
            temp.push_back(i);
            canRun = true;
            counters[i - 1]--;
          }
        }
        if (canRun)
        {
          backtracking(results, temp, counters, index + 1, k, n);
          temp.pop_back();
          counters[i - 1]++;
        }
      }
    }
  }
};

class Solution130
{
public:
  void dfs(vector<vector<char>> &board, int x, int y)
  {
    queue<pair<int, int>> q;
    q.push({x, y});
    board[x][y] = 's';
    int rows = board.size();
    int cols = board[0].size();
    while (!q.empty())
    {
      pair<int, int> position = q.front();
      q.pop();
      for (auto direction : DIRECTIONS)
      {
        int nx = position.first + direction[0];
        int ny = position.second + direction[1];
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols)
        {
          if (board[nx][ny] == 'O')
          {
            board[nx][ny] = 's';
            q.push({nx, ny});
          }
        }
      }
    }
  }

  void solve(vector<vector<char>> &board)
  {
    int rows = board.size();
    int cols = board[0].size();
    for (int i = 0; i < cols; i++)
    {
      if (board[0][i] == 'O')
        dfs(board, 0, i);
      if (board[rows - 1][i] == 'O')
        dfs(board, rows - 1, i);
    }
    for (int i = 1; i < rows - 1; i++)
    {
      if (board[i][0] == 'O')
        dfs(board, i, 0);
      if (board[i][cols - 1] == 'O')
        dfs(board, i, cols - 1);
    }
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        if (board[i][j] == 'O')
          board[i][j] = 'X';
        else if (board[i][j] == 's')
          board[i][j] = 'O';
      }
    }
  }
};

int main() {}
