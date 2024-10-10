#include <iostream>
#include <string>
#include <map>

using namespace std;

/*https://leetcode.com/problems/design-a-stack-with-increment-operation/?envType=daily-question&envId=2024-09-30*/
class CustomStack
{
public:
  int maxSize;
  int *arr;
  int begin;

  CustomStack(int maxSize)
  {
    this->maxSize = maxSize;
    arr = new int[this->maxSize];
    begin = -1;
  }

  void push(int x)
  {
    if (begin < this->maxSize - 1)
    {
      begin = begin + 1;
      arr[begin] = x;
    }
  }

  int pop()
  {
    if (begin >= 0)
      return arr[begin--];
    return -1;
  }

  void increment(int k, int val)
  {
    int total = min(begin, k - 1);
    for (int i = 0; i <= total; i++)
    {
      arr[i] += val;
    }
  }
};

void sToString(CustomStack *stack)
{
  cout << "see: ";
  for (int i = 0; i <= stack->begin; i++)
  {
    cout << stack->arr[i] << " ";
  }
  cout << endl;
}

int main()
{
  CustomStack *stack = new CustomStack(3);
  stack->push(1);
  stack->push(2);
  sToString(stack);
  cout << "pop: " << stack->pop() << endl;
  sToString(stack);
  stack->push(2);
  stack->push(3);
  stack->push(4);
  sToString(stack);
  stack->increment(5, 100);
  sToString(stack);
  stack->increment(2, 100);
  sToString(stack);
  cout << "pop: " << stack->pop() << endl;
  cout << "pop: " << stack->pop() << endl;
  cout << "pop: " << stack->pop() << endl;
  cout << "pop: " << stack->pop() << endl;
  return 0;
}