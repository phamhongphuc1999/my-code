#include <iostream>
#include <vector>
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

int main()
{
  vector<int> vec1{0, 0, 0};
  int result = threeSumClosest(vec1, 1);
  cout << result << endl;
  return 0;
}