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

int main()
{
  vector<int> vec1{1};
  cout << maxCount(vec1, 10000, 1000000000) << endl;
}