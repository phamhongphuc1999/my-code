#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <stack>
#include <unordered_map>

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

/*https://leetcode.com/problems/divide-two-integers/description/*/
long long divide(long long dividend, long long divisor)
{
  if (dividend == INT_MIN && divisor == -1)
    return INT_MAX;
  int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;

  dividend = abs(dividend);
  divisor = abs(divisor);
  long long quotient = 0;
  for (int i = 31; i >= 0; --i)
  {
    if ((divisor << i) <= dividend)
    {
      dividend -= (divisor << i);
      quotient |= (1LL << i);
    }
  }
  return sign * quotient;
}

int searchFirstRange(vector<int> &nums, int target)
{
  int start = 0;
  int end = nums.size() - 1;
  while (start < end)
  {
    if (start == end - 1)
    {
      if (nums[start] == target)
        return start;
      else if (nums[end] == target)
        return end;
      else
        return -1;
    }
    int mid = (start + end) / 2;
    if (nums[mid] < target)
      start = mid + 1;
    else if (nums[mid] > target)
      end = mid - 1;
    else
      end = mid;
  }
  return nums[start] == target ? start : -1;
}

int searchLatestRange(vector<int> &nums, int target)
{
  int start = 0;
  int end = nums.size() - 1;
  while (start < end)
  {
    if (start == end - 1)
    {
      if (nums[end] == target)
        return end;
      else if (nums[start] == target)
        return start;
      else
        return -1;
    }
    int mid = (start + end) / 2;
    if (nums[mid] < target)
      start = mid + 1;
    else if (nums[mid] > target)
      end = mid - 1;
    else
      start = mid;
  }
  return nums[end] == target ? end : -1;
}

/*https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/*/
vector<int> searchRange(vector<int> &nums, int target)
{
  if (nums.size() == 0)
    return vector<int>{-1, -1};
  int firstIndex = searchFirstRange(nums, target);
  int latestIndex = searchLatestRange(nums, target);
  return vector<int>{firstIndex, latestIndex};
}

/*https://leetcode.com/problems/minimum-string-length-after-removing-substrings/description/?envType=daily-question&envId=2024-10-07*/
int minLength(string s)
{
  int len = s.length();
  if (len <= 1)
    return len;
  stack<char> save;
  for (int i = 0; i < len; i++)
  {
    if (save.size() == 0)
      save.push(s[i]);
    else
    {
      char top = save.top();
      if (s[i] == 'B' && top == 'A')
        save.pop();
      else if (s[i] == 'D' && top == 'C')
        save.pop();
      else
        save.push(s[i]);
    }
  }
  return save.size();
}

/*https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/editorial/?envType=daily-question&envId=2024-10-08*/
int minSwaps(string s)
{
  int stackSize = 0;
  int n = s.size();

  for (int i = 0; i < n; i++)
  {
    char ch = s[i];
    if (ch == '[')
      stackSize++;
    else
    {
      if (stackSize > 0)
        stackSize--;
    }
  }
  return (stackSize + 1) / 2;
}

/*https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/description/?envType=daily-question&envId=2024-10-09*/
int minAddToMakeValid(string s)
{
  int counter = 1;
  int len = s.length();
  char c[len];
  c[0] = s[0];
  for (int i = 1; i < len; i++)
  {
    if (counter > 0 && c[counter - 1] == '(' && s[i] == ')')
      counter--;
    else
      c[counter++] = s[i];
  }
  return counter;
}

// problem 66
vector<int> plusOne(vector<int> &digits)
{
  int remaining = 1;
  vector<int> result;
  for (int i = digits.size() - 1; i >= 0; i--)
  {
    int total = remaining + digits[i];
    if (total >= 10)
    {
      remaining = 1;
      total -= 10;
    }
    else
      remaining = 0;
    result.insert(result.begin(), total);
  }
  if (remaining == 1)
    result.insert(result.begin(), 1);
  return result;
}

// problem 961
int repeatedNTimes(vector<int> &nums)
{
  unordered_map<int, int> um;
  for (int i = 0; i < nums.size(); i++)
  {
    if (um[nums[i]] > 0)
      return nums[i];
    else
      um[nums[i]] = 1;
  }
  return -1;
}

int main()
{
  vector<int> aa = {1, 2, 3, 3};
  int aaa = repeatedNTimes(aa);
  cout << aaa << endl;
}