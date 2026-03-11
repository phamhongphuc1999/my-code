#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <stack>
#include <unordered_map>

using namespace std;

/*https://leetcode.com/problems/search-insert-position/*/
int searchInsert(vector<int> &nums, int target)
{
  int len = nums.size();
  int low = 0;
  int high = len - 1;
  while (low <= high)
  {
    int mid = (low + high) / 2;
    int value = nums[mid];
    if (value < target)
      low = mid + 1;
    else if (value > target)
      high = mid - 1;
    else
      return mid;
  }
  return low;
}

/*https://leetcode.com/problems/length-of-last-word/description/*/
int lengthOfLastWord(string s)
{
  int len = s.length();
  int size = 0;
  int counter = len - 1;
  while (counter >= 0)
  {
    if (s[counter] == ' ')
      counter--;
    else
      break;
  }
  while (counter >= 0)
  {
    if (s[counter] == ' ')
      break;
    size++;
    counter--;
  }
  return size;
}

/*https://leetcode.com/problems/convert-1d-array-into-2d-array/?envType=daily-question&envId=2024-09-01*/
vector<vector<int>> construct2DArray(vector<int> &original, int m, int n)
{
  vector<vector<int>> result;
  if (m * n != original.size())
    return result;
  int counter = 0;
  int cCounter = 0;
  int rCounter = 0;
  for (int element : original)
  {
    if (cCounter == 0)
      result.push_back(vector<int>(n, 0));
    result[rCounter][cCounter++] = element;
    if (cCounter == n)
    {
      cCounter = 0;
      rCounter++;
    }
  }
  return result;
}

/*https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/description/*/
string removeDigit(string number, char digit)
{
  int len = number.length();
  string result = "";
  for (int i = 0; i < len; i++)
  {
    if (number[i] == digit)
    {
      string temp = number.substr(0, i) + number.substr(i + 1);
      if (result == "")
        result = temp;
      else
      {
        int counter = 0;
        while (counter < len - 1)
        {
          if (result[counter] > temp[counter])
            break;
          else if (result[counter] < temp[counter])
          {
            result = temp;
            break;
          }
          counter++;
        }
      }
    }
  }
  return result;
}

/*https://leetcode.com/problems/rank-transform-of-an-array/?envType=daily-question&envId=2024-10-02*/
vector<int> arrayRankTransform(vector<int> &arr)
{
  vector<int> result;
  if (arr.size() == 0)
    return result;
  vector<int> copiedArr = arr;
  sort(copiedArr.begin(), copiedArr.end());
  map<int, int> hash;
  int counter = 1;
  int preValue = copiedArr[0];
  for (int i : copiedArr)
  {
    if (i > preValue)
      counter++;
    hash.insert({i, counter});
    preValue = i;
  }
  for (int i : arr)
  {
    result.push_back(hash[i]);
  }
  return result;
}

/*https://leetcode.com/problems/permutation-in-string/description/?envType=daily-question&envId=2024-10-05*/
bool checkInclusion(string s1, string s2)
{
  int len1 = s1.length();
  int len2 = s2.length();
  if (len1 > len2)
    return false;
  int counter = 0;
  int s1Array[26]{0};
  for (char s : s1)
  {
    s1Array[s - 'a'] += 1;
  }
  int s2Array[26]{0};
  for (int i = 0; i < 26; i++)
  {
    if (s2Array[i] == s1Array[i])
      counter++;
  }
  for (int i = 0; i < len1; i++)
  {
    int value = s2[i] - 'a';
    if (s2Array[value] == s1Array[value])
      counter--;
    s2Array[value] += 1;
    if (s2Array[value] == s1Array[value])
      counter++;
  }
  if (counter == 26)
    return true;
  for (int i = len1; i < len2; i++)
  {
    int remove = s2[i - len1] - 'a';
    int add = s2[i] - 'a';
    if (s2Array[remove] == s1Array[remove])
      counter--;
    s2Array[remove] -= 1;
    if (s2Array[remove] == s1Array[remove])
      counter++;

    if (s2Array[add] == s1Array[add])
      counter--;
    s2Array[add] += 1;
    if (s2Array[add] == s1Array[add])
      counter++;
    if (counter == 26)
      return true;
  }
  return false;
}

/*https://leetcode.com/problems/divide-two-integers/description/*/
long long divide(long long dividend, long long divisor)
{
  if (dividend == INT_MIN && divisor == -1)
    return INT_MAX;
  int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;

  dividend = abs(dividend);
  divisor = abs(divisor);
  long long quotient = 0;
  for (int i = 31; i >= 0; --i)
  {
    if ((divisor << i) <= dividend)
    {
      dividend -= (divisor << i);
      quotient |= (1LL << i);
    }
  }
  return sign * quotient;
}

int searchFirstRange(vector<int> &nums, int target)
{
  int start = 0;
  int end = nums.size() - 1;
  while (start < end)
  {
    if (start == end - 1)
    {
      if (nums[start] == target)
        return start;
      else if (nums[end] == target)
        return end;
      else
        return -1;
    }
    int mid = (start + end) / 2;
    if (nums[mid] < target)
      start = mid + 1;
    else if (nums[mid] > target)
      end = mid - 1;
    else
      end = mid;
  }
  return nums[start] == target ? start : -1;
}

int searchLatestRange(vector<int> &nums, int target)
{
  int start = 0;
  int end = nums.size() - 1;
  while (start < end)
  {
    if (start == end - 1)
    {
      if (nums[end] == target)
        return end;
      else if (nums[start] == target)
        return start;
      else
        return -1;
    }
    int mid = (start + end) / 2;
    if (nums[mid] < target)
      start = mid + 1;
    else if (nums[mid] > target)
      end = mid - 1;
    else
      start = mid;
  }
  return nums[end] == target ? end : -1;
}

/*https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/*/
vector<int> searchRange(vector<int> &nums, int target)
{
  if (nums.size() == 0)
    return vector<int>{-1, -1};
  int firstIndex = searchFirstRange(nums, target);
  int latestIndex = searchLatestRange(nums, target);
  return vector<int>{firstIndex, latestIndex};
}

/*https://leetcode.com/problems/minimum-string-length-after-removing-substrings/description/?envType=daily-question&envId=2024-10-07*/
int minLength(string s)
{
  int len = s.length();
  if (len <= 1)
    return len;
  stack<char> save;
  for (int i = 0; i < len; i++)
  {
    if (save.size() == 0)
      save.push(s[i]);
    else
    {
      char top = save.top();
      if (s[i] == 'B' && top == 'A')
        save.pop();
      else if (s[i] == 'D' && top == 'C')
        save.pop();
      else
        save.push(s[i]);
    }
  }
  return save.size();
}

/*https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/editorial/?envType=daily-question&envId=2024-10-08*/
int minSwaps(string s)
{
  int stackSize = 0;
  int n = s.size();

  for (int i = 0; i < n; i++)
  {
    char ch = s[i];
    if (ch == '[')
      stackSize++;
    else
    {
      if (stackSize > 0)
        stackSize--;
    }
  }
  return (stackSize + 1) / 2;
}

/*https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/description/?envType=daily-question&envId=2024-10-09*/
int minAddToMakeValid(string s)
{
  int counter = 1;
  int len = s.length();
  char c[len];
  c[0] = s[0];
  for (int i = 1; i < len; i++)
  {
    if (counter > 0 && c[counter - 1] == '(' && s[i] == ')')
      counter--;
    else
      c[counter++] = s[i];
  }
  return counter;
}

// problem 66
vector<int> plusOne(vector<int> &digits)
{
  int remaining = 1;
  vector<int> result;
  for (int i = digits.size() - 1; i >= 0; i--)
  {
    int total = remaining + digits[i];
    if (total >= 10)
    {
      remaining = 1;
      total -= 10;
    }
    else
      remaining = 0;
    result.insert(result.begin(), total);
  }
  if (remaining == 1)
    result.insert(result.begin(), 1);
  return result;
}

// problem 961
int repeatedNTimes(vector<int> &nums)
{
  unordered_map<int, int> um;
  for (int i = 0; i < nums.size(); i++)
  {
    if (um[nums[i]] > 0)
      return nums[i];
    else
      um[nums[i]] = 1;
  }
  return -1;
}

class Solution36
{
public:
  bool isValidSudoku(vector<vector<char>> &board)
  {
    // row
    for (int i = 0; i < 9; i++)
    {
      bool seen[10] = {false};
      for (int j = 0; j < 9; j++)
      {
        if (board[i][j] != '.')
        {
          if (seen[board[i][j] - '0'])
            return false;
          seen[board[i][j] - '0'] = true;
        }
      }
    }

    // colume
    for (int i = 0; i < 9; i++)
    {
      bool seen[10] = {false};
      for (int j = 0; j < 9; j++)
      {
        if (board[j][i] != '.')
        {
          if (seen[board[j][i] - '0'])
            return false;
          seen[board[j][i] - '0'] = true;
        }
      }
    }

    // block
    for (int i = 0; i < 9; i = i + 3)
    {
      for (int j = 0; j < 9; j = j + 3)
      {
        bool seen[10] = {false};
        for (int i1 = 0; i1 <= 2; i1++)
        {
          for (int j1 = 0; j1 <= 2; j1++)
          {
            if (board[i + i1][j + j1] != '.')
            {
              int value = board[i + i1][j + j1] - '0';
              if (seen[value])
                return false;
              seen[value] = true;
            }
          }
        }
      }
    }

    return true;
  }
};

class Solution2133
{
public:
  bool checkValid(vector<vector<int>> &matrix)
  {
    int n = matrix.size();
    for (int i = 0; i < n; i++)
    {
      vector<bool> rows(n + 1, false);
      vector<bool> columns(n + 1, false);
      for (int j = 0; j < n; j++)
      {
        int row = matrix[i][j];
        int column = matrix[j][i];
        if (rows[row])
          return false;
        else
          rows[row] = true;
        if (columns[column])
          return false;
        else
          columns[column] = true;
      }
    }
    return true;
  }
};

class Solution37
{
public:
  pair<int, int> nextIndex(int row, int column)
  {
    if (column == 8)
      return {row + 1, 0};
    else
      return {row, column + 1};
  }

  bool dfs(vector<vector<char>> &board, int row, int column)
  {
    if (row == 9)
      return true;

    auto next = nextIndex(row, column);

    if (board[row][column] != '.')
      return dfs(board, next.first, next.second);

    bool seen[10] = {false};

    for (int i = 0; i < 9; i++)
    {
      if (board[row][i] != '.')
        seen[board[row][i] - '0'] = true;

      if (board[i][column] != '.')
        seen[board[i][column] - '0'] = true;
    }

    int r = (row / 3) * 3;
    int c = (column / 3) * 3;

    for (int i = r; i < r + 3; i++)
      for (int j = c; j < c + 3; j++)
        if (board[i][j] != '.')
          seen[board[i][j] - '0'] = true;

    for (int i = 1; i <= 9; i++)
    {
      if (!seen[i])
      {
        board[row][column] = '0' + i;

        if (dfs(board, next.first, next.second))
          return true;

        board[row][column] = '.';
      }
    }

    return false;
  }

  void solveSudoku(vector<vector<char>> &board)
  {
    dfs(board, 0, 0);
  }
};

class Solution1009
{
public:
  int bitwiseComplement(int n)
  {
    int mask = 1;
    while (mask < n)
      mask = (mask << 1) | 1; // build 0111...1
    return n ^ mask;
  }
};

class Solution980
{
  int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

public:
  bool dfs(vector<vector<int>> &grid, pair<int, int> position, int steps, int total, int &result)
  {
    if (grid[position.first][position.second] == 2)
      return steps == total;
    int rows = grid.size();
    int cols = grid[0].size();
    for (auto direction : directions)
    {
      int _first = position.first + direction[0];
      int _second = position.second + direction[1];
      if (_first < 0 || _first >= rows || _second < 0 || _second >= cols)
        continue;
      if (grid[_first][_second] == 0 || grid[_first][_second] == 2)
      {
        if (grid[_first][_second] != 2)
          grid[_first][_second] = -1;
        bool check = dfs(grid, {_first, _second}, steps + 1, total, result);
        if (check)
          result++;
        if (grid[_first][_second] != 2)
          grid[_first][_second] = 0;
      }
    }
    return false;
  }

  int uniquePathsIII(vector<vector<int>> &grid)
  {
    int rows = grid.size();
    int cols = grid[0].size();
    int total = 0;
    pair<int, int> begin;
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        if (grid[i][j] != -1)
        {
          total++;
          if (grid[i][j] == 1)
          {
            begin = {i, j};
          }
        }
      }
    }
    int result = 0;
    dfs(grid, begin, 1, total, result);
    return result;
  }
};
