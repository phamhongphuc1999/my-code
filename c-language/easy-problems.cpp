#include <iostream>
#include <vector>
#include <bits/stdc++.h>

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

/*https://leetcode.com/problems/rank-transform-of-an-array/?envType=daily-question&envId=2024-10-02*/
vector<int> arrayRankTransform(vector<int> &arr)
{
  vector<int> result;
  if (arr.size() == 0)
    return result;
  vector<int> copiedArr = arr;
  sort(copiedArr.begin(), copiedArr.end());
  map<int, int> hash;
  int counter = 1;
  int preValue = copiedArr[0];
  for (int i : copiedArr)
  {
    if (i > preValue)
      counter++;
    hash.insert({i, counter});
    preValue = i;
  }
  for (int i : arr)
  {
    result.push_back(hash[i]);
  }
  return result;
}

/*https://leetcode.com/problems/permutation-in-string/description/?envType=daily-question&envId=2024-10-05*/
bool checkInclusion(string s1, string s2)
{
  int len1 = s1.length();
  int len2 = s2.length();
  if (len1 > len2)
    return false;
  int counter = 0;
  int s1Array[26]{0};
  for (char s : s1)
  {
    s1Array[s - 'a'] += 1;
  }
  int s2Array[26]{0};
  for (int i = 0; i < 26; i++)
  {
    if (s2Array[i] == s1Array[i])
      counter++;
  }
  for (int i = 0; i < len1; i++)
  {
    int value = s2[i] - 'a';
    if (s2Array[value] == s1Array[value])
      counter--;
    s2Array[value] += 1;
    if (s2Array[value] == s1Array[value])
      counter++;
  }
  if (counter == 26)
    return true;
  for (int i = len1; i < len2; i++)
  {
    int remove = s2[i - len1] - 'a';
    int add = s2[i] - 'a';
    if (s2Array[remove] == s1Array[remove])
      counter--;
    s2Array[remove] -= 1;
    if (s2Array[remove] == s1Array[remove])
      counter++;

    if (s2Array[add] == s1Array[add])
      counter--;
    s2Array[add] += 1;
    if (s2Array[add] == s1Array[add])
      counter++;
    if (counter == 26)
      return true;
  }
  return false;
}

int main()
{
  cout << checkInclusion("ab", "eidboaoo") << endl;
  cout << endl;
  return 0;
}