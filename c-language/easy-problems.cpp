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

/*https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/description/*/
string removeDigit(string number, char digit)
{
  int len = number.length();
  string result = "";
  for (int i = 0; i < len; i++)
  {
    if (number[i] == digit)
    {
      string temp = number.substr(0, i) + number.substr(i + 1);
      if (result == "")
        result = temp;
      else
      {
        int counter = 0;
        while (counter < len - 1)
        {
          if (result[counter] > temp[counter])
            break;
          else if (result[counter] < temp[counter])
          {
            result = temp;
            break;
          }
          counter++;
        }
      }
    }
  }
  return result;
}

int main()
{
  cout << removeDigit("551", '5') << endl;
  return 0;
}