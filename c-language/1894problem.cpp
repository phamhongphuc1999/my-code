#include <iostream>
#include <vector>

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

int main()
{
  vector<int> vect1{3, 4, 1, 2};
  int result = chalkReplacer(vect1, 30);
  cout << result << endl;
}