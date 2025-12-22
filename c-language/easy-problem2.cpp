#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <stack>
#include <string>

using namespace std;

vector<int> getFinalState(vector<int> &nums, int k, int multiplier)
{
  priority_queue<int, vector<int>, greater<int>> pq;
  map<int, priority_queue<int, vector<int>, greater<int>>> hash;
  int counter = 0;
  for (int num : nums)
  {
    pq.push(num);
    map<int, priority_queue<int, vector<int>, greater<int>>>::iterator temp = hash.find(num);
    if (hash.find(num) != hash.end())
      hash[num].push(counter);
    else
    {
      priority_queue<int, vector<int>, greater<int>> _temp;
      _temp.push(counter);
      hash.insert({num, _temp});
    }
    counter++;
  }
  for (int i = 0; i < k; i++)
  {
    int minValue = pq.top();
    pq.pop();
    int newValue = minValue * multiplier;
    int index = hash[minValue].top();
    hash[minValue].pop();
    nums[index] = newValue;

    pq.push(newValue);
    map<int, priority_queue<int, vector<int>, greater<int>>>::iterator check = hash.find(newValue);
    if (check != hash.end())
    {
      hash[newValue].push(index);
    }
    else
    {
      priority_queue<int, vector<int>, greater<int>> _new;
      _new.push(index);
      hash.insert({newValue, _new});
    }
  }
  return nums;
}

bool canThreePartsEqualSum(vector<int> &arr)
{
  int total = 0;
  for (int i : arr)
    total += i;
  if (total % 3 != 0)
    return false;
  int targetTotal = total / 3;
  int remaining = targetTotal;
  int okCounter = 0;
  bool isFinalRound = false;
  int finalRound = targetTotal;
  for (int i : arr)
  {
    if (okCounter < 2)
    {
      remaining -= i;
      if (remaining == 0)
      {
        okCounter++;
        remaining = targetTotal;
      }
    }
    else
    {
      finalRound -= i;
      isFinalRound = true;
    }
  }
  return finalRound == 0 && okCounter == 2 && isFinalRound;
}

// 3432. Count Partitions with Even Sum Difference
int countPartitions(vector<int> &nums)
{
  int total = 0;
  for (int item : nums)
  {
    total += item;
  }
  int firstTotal = 0;
  int result = 0;
  for (int i = 0; i < nums.size() - 1; i++)
  {
    firstTotal += nums.at(i);
    if ((2 * firstTotal - total) % 2 == 0)
      result++;
  }
  return result;
}

string phoneNumbers[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

struct Node
{
  string arr;
  int prevIndex;
};

// 17. Letter Combinations of a Phone Number
vector<string> letterCombinations(string digits)
{
  vector<string> result;
  stack<Node> st;
  int index = digits[0] - '0' - 2;
  for (char _char : phoneNumbers[index])
  {
    st.push({string("") + _char, 0});
  }
  while (st.size() > 0)
  {
    Node item = st.top();
    int currentIndex = item.prevIndex + 1;
    if (currentIndex == digits.length())
    {
      string _value = item.arr;
      result.push_back(_value);
      st.pop();
    }
    else
    {
      string _value = item.arr;
      int index = digits[currentIndex] - '0' - 2;
      st.pop();
      for (char _char : phoneNumbers[index])
      {
        st.push({_value + _char, currentIndex});
      }
    }
  }

  return result;
}

int main()
{
  vector<string> result = letterCombinations("2");
  cout << 1 << endl;
  for (string value : result)
  {
    cout << value << endl;
  }
}
