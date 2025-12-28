#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <cstdint>
#include <map>

using namespace std;

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

int main()
{
  vector<int> aaa{1, -2, -5, -4, -3, 3, 3, 5};
  vector<vector<int>> result = fourSum(aaa, -11);
  for (vector<int> item : result)
  {
    for (int i : item)
    {
      cout << i << ", ";
    }
    cout << endl;
  }
}