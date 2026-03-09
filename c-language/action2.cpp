#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/*https://leetcode.com/problems/design-circular-deque/?envType=daily-question&envId=2024-09-28*/
class MyCircularDeque
{
public:
  int maxSize;
  int size;
  int *save;
  int begin;
  int end;

  MyCircularDeque(int k)
  {
    this->maxSize = k;
    this->size = 0;
    save = new int[k];
    begin = -1;
    end = 0;
  }

  bool insertFront(int value)
  {
    if (this->size == this->maxSize)
      return false;
    if (begin < maxSize - 1)
      begin++;
    else
      begin = 0;
    this->save[begin] = value;
    this->size++;
    return true;
  }

  bool insertLast(int value)
  {
    if (this->size == this->maxSize)
      return false;
    if (end > 0)
      end--;
    else
      end = maxSize - 1;
    this->save[end] = value;
    this->size++;
    return true;
  }

  bool deleteFront()
  {
    if (this->size == 0)
      return false;
    if (begin > 0)
      begin--;
    else
      begin = maxSize - 1;
    this->size--;
    return true;
  }

  bool deleteLast()
  {
    if (this->size == 0)
      return false;
    if (end < maxSize - 1)
      end++;
    else
      end = 0;
    this->size--;
    return true;
  }

  int getFront()
  {
    if (this->size == 0)
      return -1;
    return save[begin];
  }

  int getRear()
  {
    if (this->size == 0)
      return -1;
    return save[end];
  }

  bool isEmpty()
  {
    return this->size == 0;
  }

  bool isFull()
  {
    return this->size == this->maxSize;
  }
};

class Solution1758
{
public:
  int minOperations(string s)
  {
    int diff = 0;
    for (int i = 0; i < s.length(); i++)
    {
      if (i % 2 == 0)
      {
        if (s[i] == '1')
          diff++;
      }
      else
      {
        if (s[i] == '0')
          diff++;
      }
    }
    return min(diff, (int)s.length() - diff);
  }
};

class Solution89
{
public:
  bool differByOneBit(int a, int b)
  {
    int x = a ^ b;
    return x && !(x & (x - 1));
  }

  bool dfs(int bits, vector<int> &result, vector<bool> &visited)
  {

    int total = 1 << bits;

    if (result.size() == total)
      return differByOneBit(result.back(), result[0]);

    for (int i = 0; i < bits; i++)
    {

      int newNum = result.back() ^ (1 << i);

      if (!visited[newNum])
      {

        visited[newNum] = true;
        result.push_back(newNum);

        if (dfs(bits, result, visited))
          return true;

        result.pop_back();
        visited[newNum] = false;
      }
    }

    return false;
  }

  vector<int> grayCode(int n)
  {

    vector<int> result;
    vector<bool> visited(1 << n, false);

    result.push_back(0);
    visited[0] = true;

    dfs(n, result, visited);

    return result;
  }
};

class Solution1784
{
public:
  bool checkOnesSegment(string s)
  {
    int counter = 0;
    for (char c : s)
    {
      if (c == '0')
        counter++;
      if (c == '1' && counter > 0)
        return false;
    }
    return true;
  }
};

int main()
{
  Solution89 s = Solution89();
  vector<int> result = s.grayCode(2);
  for (int item : result)
  {
    cout << item << endl;
  }
}

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

// problem 1970
struct Node
{
  int row;
  int column;
  int direction; // 0-up, 1-down, 2-left, 3-right
};

class Solution
{
public:
  bool canCross(int row, int col, vector<vector<int>> &cells, int day)
  {
    vector<vector<int>> grid(row, vector<int>(col, 1));

    for (int i = 0; i <= day; i++)
    {
      grid[cells[i][0] - 1][cells[i][1] - 1] = 0;
    }

    queue<pair<int, int>> q;

    for (int c = 0; c < col; c++)
    {
      if (grid[0][c] == 1)
      {
        q.push({0, c});
        grid[0][c] = 2;
      }
    }

    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!q.empty())
    {
      auto [r, c] = q.front();
      q.pop();
      if (r == row - 1)
        return true;

      for (auto &d : dirs)
      {
        int nr = r + d[0], nc = c + d[1];
        if (nr >= 0 && nr < row && nc >= 0 && nc < col && grid[nr][nc] == 1)
        {
          grid[nr][nc] = 2;
          q.push({nr, nc});
        }
      }
    }

    return false;
  }

  bool dfs(vector<vector<int>> &lands, int row, int col, vector<Node> &result)
  {
    if (result.size() == 0)
    {
      for (int i = 0; i < col; i++)
      {
        if (lands[0][i] == 1)
        {
          result.push_back({0, i, 0});
          lands[0][i] = 2;
          if (dfs(lands, row, col, result))
            return true;
          result.pop_back();
          lands[0][i] = 1;
        }
      }
      return false;
    }
    else
    {
      Node temp = result.back();
      if (temp.row == row - 1)
        return true;
      if (temp.direction != 0 && temp.row > 0 && lands[temp.row - 1][temp.column] == 1)
      {
        result.push_back({temp.row - 1, temp.column, 1});
        lands[temp.row - 1][temp.column] = 2;
        if (dfs(lands, row, col, result))
          return true;
        result.pop_back();
        lands[temp.row - 1][temp.column] = 1;
      }
      if (temp.direction != 1 && temp.row < row - 1 && lands[temp.row + 1][temp.column] == 1)
      {
        result.push_back({temp.row + 1, temp.column, 0});
        lands[temp.row + 1][temp.column] = 2;
        if (dfs(lands, row, col, result))
          return true;
        result.pop_back();
        lands[temp.row + 1][temp.column] = 1;
      }
      if (temp.direction != 2 && temp.column > 0 && lands[temp.row][temp.column - 1] == 1)
      {
        result.push_back({temp.row, temp.column - 1, 3});
        lands[temp.row][temp.column - 1] = 2;
        if (dfs(lands, row, col, result))
          return true;
        result.pop_back();
        lands[temp.row][temp.column - 1] = 1;
      }
      if (temp.direction != 3 && temp.column < col - 1 && lands[temp.row][temp.column + 1] == 1)
      {
        result.push_back({temp.row, temp.column + 1, 2});
        lands[temp.row][temp.column + 1] = 2;
        if (dfs(lands, row, col, result))
          return true;
        result.pop_back();
        lands[temp.row][temp.column + 1] = 1;
      }
      return false;
    }
  }

  vector<Node> findPath(int row, int col, vector<vector<int>> &cells, int index)
  {
    vector<vector<int>> lands(row, vector<int>(col, 1));

    for (int i = 0; i <= index; i++)
    {
      int r = cells[i][0] - 1;
      int c = cells[i][1] - 1;
      lands[r][c] = 0;
    }
    vector<Node> result;
    dfs(lands, row, col, result);
    return result;
  }
  int latestDayToCross(int row, int col, vector<vector<int>> &cells)
  {
    int left = 0;
    int right = cells.size() - 1;
    int ans = -1;

    while (left <= right)
    {
      int mid = left + (right - left) / 2;

      if (canCross(row, col, cells, mid))
      {
        ans = mid;
        left = mid + 1;
      }
      else
      {
        right = mid - 1;
      }
    }
    return ans + 1;
  }
};

char nextGreatestLetter(vector<char> &letters, char target)
{
  int begin = 0;
  int end = letters.size() - 1;
  int result = 0;
  while (begin <= end)
  {
    int middle = (begin + end) / 2;
    if (letters[middle] <= target)
    {
      begin = middle + 1;
    }
    else
    {
      end = middle - 1;
      result = middle;
    }
  }
  return letters[result];
}

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

/*https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/description/?envType=daily-question&envId=2024-09-02*/
int chalkReplacer(vector<int> &chalk, int k)
{
  int _size = chalk.size();
  unsigned long int total[chalk.size() + 1];
  total[0] = 0;
  int counter = 1;
  for (int item : chalk)
  {
    total[counter] = total[counter - 1] + item;
    counter = counter + 1;
  }
  int remainder = k % total[_size];
  int begin = 1;
  int end = _size;
  while (begin <= end)
  {
    int mid = (begin + end) / 2;
    if (total[mid] < remainder)
      begin = mid + 1;
    else if (total[mid] > remainder)
      end = mid - 1;
    else
      return mid;
  }
  return begin - 1;
}

/*https://leetcode.com/problems/sentence-similarity-iii/description/?envType=daily-question&envId=2024-10-06*/
bool areSentencesSimilar(string sentence1, string sentence2)
{
  stringstream ss1(sentence1), ss2(sentence2);
  string word;
  vector<string> vec1, vec2;
  while (ss1 >> word)
    vec1.push_back(word);
  while (ss2 >> word)
    vec2.push_back(word);
  if (vec1.size() > vec2.size())
    return areSentencesSimilar(sentence2, sentence1);
  int start = 0;
  int end1 = vec1.size() - 1;
  int end2 = vec2.size() - 1;
  while (start < vec1.size() && vec1[start] == vec2[start])
  {
    start++;
  }
  while (end1 >= 0 && end2 >= 0 && vec1[end1] == vec2[end2])
  {
    end1--;
    end2--;
  }
  return start >= end1 + 1;
}
