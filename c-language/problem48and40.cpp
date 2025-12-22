#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>
#include <unordered_map>

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

struct FourSumNode
{
  vector<int> arr;
  string key;
  int latestIndex;
  int total;
};

// 18. 4Sum
vector<vector<int>> fourSum(vector<int> &nums, int target)
{
  vector<vector<int>> result;
  if (nums.size() < 4)
    return result;
  sort(nums.begin(), nums.end());
  stack<FourSumNode> st;
  unordered_map<string, bool> mp;
  for (int i = 0; i < nums.size() - 3; i++)
  {
    string _key = to_string(nums[i]);
    if (mp.count(_key) == 0)
      st.push({{nums[i]}, _key, i, nums[i]});
    mp.insert({_key, true});
  }
  while (st.size() > 0)
  {
    FourSumNode item = st.top();
    st.pop();
    if (item.arr.size() == 4)
    {
      if (item.total == target)
        result.push_back(item.arr);
    }
    else if (item.arr.size() < 4)
    {
      for (int i = item.latestIndex + 1; i < nums.size(); i++)
      {
        string _key = item.key + "_" + to_string(nums[i]);
        if (mp.count(_key) == 0)
        {
          vector<int> curr = item.arr;
          curr.push_back(nums[i]);
          int total = item.total + nums[i];
          st.push({curr, _key, i, total});
          mp.insert({_key, true});
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

int main()
{
  vector<int> a = {-5, 5, 4, -3, 0, 0, 4, -2};
  vector<vector<int>> result = fourSum(a, 4);
  for (vector<int> item : result)
  {
    for (int value : item)
    {
      cout << value << ", ";
    }
    cout << endl;
  }
}