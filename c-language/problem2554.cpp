#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

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

// problem 47
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

// problem 77
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

int main()
{
  Solution77 s = Solution77();
  vector<vector<int>> results = s.combine(1, 1);
  for (vector<int> item : results)
  {
    for (int i : item)
    {
      cout << i << ", ";
    }
    cout << endl;
  }
}