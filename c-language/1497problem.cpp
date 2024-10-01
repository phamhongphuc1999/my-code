#include <iostream>
#include <map>
#include <vector>

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

int main()
{
  vector<int> vec1{-1, -1, -1, -1, 2, 2, -2, -2};
  cout << canArrange(vec1, 3) << endl;
  return 0;
}