#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

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

int main()
{
  bool check = areSentencesSimilar("My name is Haley", "My Haley");
  cout << check << endl;
}