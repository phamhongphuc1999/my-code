#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

int sumClosest(vector<int> &nums, int start, int end, int target)
{
  int down = start;
  int up = end;
  int result = nums[start] + nums[end];
  int check = abs(target - result);
  while (down < up)
  {
    int temp = nums[down] + nums[up];
    int _check = temp - target;
    if (_check < 0)
      down = down + 1;
    else if (_check > 0)
      up--;
    else
      return temp;
    if (check > abs(_check))
    {
      check = abs(_check);
      result = temp;
    }
  }
  return result;
}

/*https://leetcode.com/problems/3sum-closest/description/*/
int threeSumClosest(vector<int> &nums, int target)
{
  int check = INT_MAX;
  int result = 0;
  sort(nums.begin(), nums.end());
  int size = nums.size() - 1;
  for (int i = 0; i < size - 1; i++)
  {
    int item = nums[i];
    int total = sumClosest(nums, i + 1, size, target - item) + item;
    int _check = abs(total - target);
    if (_check == 0)
      return target;
    else if (_check < check)
    {
      check = _check;
      result = total;
    }
  }
  return result;
}

// problem 45
int jump(vector<int> &nums)
{
  int _size = nums.size();
  int steps[_size];
  memset(steps, 0, sizeof(steps));
  for (int i = _size - 2; i >= 0; i--)
  {
    int possibleSteps = nums[i];
    if (possibleSteps == 0)
    {
      steps[i] = _size;
      continue;
    }
    int minSteps = _size * 2;
    int offset = 1;
    while (offset <= possibleSteps && i + offset < _size)
    {
      int step = steps[i + offset];
      if (minSteps > step)
        minSteps = step;
      offset++;
    }
    steps[i] = minSteps + 1;
  }
  return steps[0];
}

int jump1(vector<int> &nums)
{
  int n = nums.size();
  int jumps = 0;
  int currentEnd = 0;
  int farthest = 0;

  for (int i = 0; i < n - 1; i++)
  {
    farthest = max(farthest, i + nums[i]);

    if (i == currentEnd)
    {
      jumps++;
      currentEnd = farthest;
    }
  }
  return jumps;
}

int main()
{
  vector<int> a = {2, 3, 0, 1, 4};
  int result = jump(a);
  cout << result << endl;
}
