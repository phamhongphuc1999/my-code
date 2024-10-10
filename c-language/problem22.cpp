#include <iostream>
#include <vector>

using namespace std;

void generate(vector<string> &result, string temp, char item, int openCounter, int closeCounter, int index, int len)
{
  if (temp.length() < len * 2)
  {
    if (index == 0)
    {
      temp = "(";
      if (len > 1)
        generate(result, temp, '(', 2, 0, 1, len);
      generate(result, temp, ')', 1, 1, 1, len);
    }
    else
    {
      temp += item;
      if (temp.length() == 2 * len)
        result.push_back(temp);
      else
      {
        if (openCounter > closeCounter)
          generate(result, temp, ')', openCounter, closeCounter + 1, index + 1, len);
        if (openCounter < len)
          generate(result, temp, '(', openCounter + 1, closeCounter, index + 1, len);
      }
    }
  }
}

/*https://leetcode.com/problems/generate-parentheses/description/*/
vector<string> generateParenthesis(int n)
{
  vector<string> result;
  generate(result, "", '1', 0, 0, 0, n);
  return result;
}

/*https://leetcode.com/problems/maximum-width-ramp/description/?envType=daily-question&envId=2024-10-10*/
int maxWidthRamp(vector<int> &nums)
{
  int size = nums.size();
  int rightMax[size];
  rightMax[size - 1] = nums[size - 1];
  for (int i = size - 2; i >= 0; i--)
  {
    rightMax[i] = max(rightMax[i + 1], nums[i]);
  }
  int left = 0;
  int right = 0;
  int _max = 0;
  while (right < size)
  {
    while (left < right && nums[left] > rightMax[right])
    {
      left++;
    }
    _max = max(_max, right - left);
    right++;
  }
  return _max;
}

int main()
{
  vector<string> result = generateParenthesis(1);
  for (string i : result)
  {
    cout << i << endl;
  }
  return 0;
}