#include <iostream>
#include <vector>

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

int main()
{
  vector<int> vect1{3};
  vector<vector<int>> result = construct2DArray(vect1, 1, 2);
  for (vector<int> list : result)
  {
    for (int item : list)
    {
      cout << item << " ";
    }
    cout << endl;
  }
  cout << endl;
  return 0;
}