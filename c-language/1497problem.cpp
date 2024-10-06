#include <iostream>
#include <map>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

/*https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/description/?envType=daily-question&envId=2024-10-01*/
bool canArrange(vector<int> &arr, int k)
{
  int half = k / 2;
  int *remainders = new int[half + 1]{0};
  for (int item : arr)
  {
    int r = item % k;
    if (r < 0)
      r = r + k;
    if (r <= half)
      remainders[r] += 1;
    else
      remainders[k - r] -= 1;
  }
  for (int i = 0; i <= half; i++)
  {
    if (remainders[i] < 0 || remainders[i] % 2 == 1)
      return false;
  }
  return true;
}

/*https://leetcode.com/problems/divide-players-into-teams-of-equal-skill/?envType=daily-question&envId=2024-10-04*/
long long dividePlayers(vector<int> &skill)
{
  sort(skill.begin(), skill.end());
  int len = skill.size();
  int check = skill[0] + skill[len - 1];
  long long result = skill[0] * skill[len - 1];
  for (int i = 1; i < len / 2; i++)
  {
    if (skill[i] + skill[len - 1 - i] != check)
      return -1;
    result += skill[i] * skill[len - 1 - i];
  }
  return result;
}

int main()
{
  vector<int> vec1{1, 1, 2, 3};
  cout << dividePlayers(vec1) << endl;
  return 0;
}