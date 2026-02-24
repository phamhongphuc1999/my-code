#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>
#include "header.h"

using namespace std;

int sumClosest(vector<int> &nums, int start, int end, int target)
{
  int down = start;
  int up = end;
  int result = nums[start] + nums[end];
  int check = abs(target - result);
  while (down < up)
  {
    int temp = nums[down] + nums[up];
    int _check = temp - target;
    if (_check < 0)
      down = down + 1;
    else if (_check > 0)
      up--;
    else
      return temp;
    if (check > abs(_check))
    {
      check = abs(_check);
      result = temp;
    }
  }
  return result;
}

/*https://leetcode.com/problems/3sum-closest/description/*/
int threeSumClosest(vector<int> &nums, int target)
{
  int check = INT_MAX;
  int result = 0;
  sort(nums.begin(), nums.end());
  int size = nums.size() - 1;
  for (int i = 0; i < size - 1; i++)
  {
    int item = nums[i];
    int total = sumClosest(nums, i + 1, size, target - item) + item;
    int _check = abs(total - target);
    if (_check == 0)
      return target;
    else if (_check < check)
    {
      check = _check;
      result = total;
    }
  }
  return result;
}

// problem 45
int jump(vector<int> &nums)
{
  int _size = nums.size();
  int steps[_size];
  memset(steps, 0, sizeof(steps));
  for (int i = _size - 2; i >= 0; i--)
  {
    int possibleSteps = nums[i];
    if (possibleSteps == 0)
    {
      steps[i] = _size;
      continue;
    }
    int minSteps = _size * 2;
    int offset = 1;
    while (offset <= possibleSteps && i + offset < _size)
    {
      int step = steps[i + offset];
      if (minSteps > step)
        minSteps = step;
      offset++;
    }
    steps[i] = minSteps + 1;
  }
  return steps[0];
}

int jump1(vector<int> &nums)
{
  int n = nums.size();
  int jumps = 0;
  int currentEnd = 0;
  int farthest = 0;

  for (int i = 0; i < n - 1; i++)
  {
    farthest = max(farthest, i + nums[i]);

    if (i == currentEnd)
    {
      jumps++;
      currentEnd = farthest;
    }
  }
  return jumps;
}

class Solution1161
{
public:
  int maxLevelSum(TreeNode *root)
  {
    int maxValue = root->val;
    int maxLevel = 1;
    queue<TreeNode *> q;
    q.push(root);
    int currentLevel = 1;
    while (!q.empty())
    {
      int size = q.size();
      int total = 0;
      for (int i = 0; i < size; i++)
      {
        TreeNode *temp = q.front();
        total += temp->val;
        q.pop();
        if (temp->left != NULL)
          q.push(temp->left);
        if (temp->right != NULL)
          q.push(temp->right);
      }
      if (total > maxValue)
      {
        maxValue = total;
        maxLevel = currentLevel;
      }
      currentLevel++;
    }
    return maxLevel;
  }
};

class Solution1339
{
  static const int MOD = 1e9 + 7;
  long long totalSum = 0;
  long long _maxProduct = 0;

public:
  long long total(TreeNode *root)
  {
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
      TreeNode *temp = q.front();
      totalSum += temp->val;
      if (temp->left != NULL)
        q.push(temp->left);
      if (temp->right != NULL)
        q.push(temp->right);
      q.pop();
    }
    return totalSum;
  }
  long long dfs(TreeNode *root)
  {
    if (root == NULL)
      return 0;
    long long left = dfs(root->left);
    long long right = dfs(root->right);
    long long _total = root->val + left + right;
    long long remainTotal = totalSum - _total;
    long long product = _total * remainTotal;
    _maxProduct = max(_maxProduct, product);
    return _total;
  }
  int maxProduct(TreeNode *root)
  {
    total(root);
    dfs(root);
    return _maxProduct % MOD;
  }
};

// problem 1458
class Solution1458
{
public:
  int maxDotProduct(vector<int> &nums1, vector<int> &nums2)
  {
    int n = nums1.size();
    int m = nums2.size();
    const long long NEG_INF = -1e18;
    vector<vector<long long>> dp(n, vector<long long>(m, NEG_INF));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        long long take = (long long)nums1[i] * nums2[j];
        if (i > 0 && j > 0)
        {
          take += max(0LL, dp[i - 1][j - 1]);
        }
        long long skip1 = (i > 0) ? dp[i - 1][j] : NEG_INF;
        long long skip2 = (j > 0) ? dp[i][j - 1] : NEG_INF;

        dp[i][j] = max({take, skip1, skip2});
      }
    }
    return dp[n - 1][m - 1];
  }
};

class Solution10
{
public:
  bool isMatch(string s, string p)
  {
    int sLen = s.length();
    int pLen = p.length();
    vector<int> dp(pLen, 0);
    if (p[0] == '.' || p[0] == s[0])
      dp[0] = 1;
    else
      dp[0] = 0;
    for (int i = 1; i < pLen; i++)
    {
      int preMaxMatchIndex = dp[i - 1];
      if (preMaxMatchIndex >= sLen - 1)
        return true;
      char currentP = p[i];
      int count = preMaxMatchIndex + 1;
      if (currentP == '.')
        dp[i] = count;
      else if (currentP == '*')
      {
        char preChar = p[i - 1];
        if (preChar == '.')
          return true;
        while (count < sLen)
        {
          if (s[count] == preChar)
            count++;
          else
            break;
        }
        dp[i] = count;
      }
      else
      {
        if (currentP == s[count])
          dp[i] = count;
        else
          return false;
      }
    }
    return dp[pLen - 1] >= sLen;
  }
};

class Solution1022
{
public:
  int dfs(TreeNode *node, int current)
  {
    if (node == NULL)
      return 0;
    current = (current << 1) | node->val;
    if (!node->left && !node->right)
      return current;

    return dfs(node->left, current) + dfs(node->right, current);
  }

  int sumRootToLeaf(TreeNode *root)
  {
    return dfs(root, 0);
  }
};

int main()
{
  Solution10 s = Solution10();
  cout << s.isMatch("mississippi", "mis*is*p*.") << endl;
}
