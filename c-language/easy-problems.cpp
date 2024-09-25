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

int main()
{
  int result = lengthOfLastWord("luffy is still joyboy");
  cout << result;
  cout << endl;
  return 0;
}