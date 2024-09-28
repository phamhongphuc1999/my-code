#include <iostream>
#include <string>

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

int main()
{
  MyCircularDeque *obj = new MyCircularDeque(3);
  string fns[11] = {"insertFront", "getRear", "insertFront", "getRear", "insertLast", "getFront", "getRear", "getFront", "insertLast", "deleteLast", "getFront"};
  int params[11] = {9, 0, 9, 0, 5, 0, 0, 0, 8, 0, 0};
  for (int i = 0; i < 11; i++)
  {
    string fn = fns[i];
    cout << fn << ": ";
    if (fn == "insertFront")
      cout << "params: " << params[i] << " result: " << obj->insertFront(params[i]) << endl;
    else if (fn == "insertLast")
      cout << "params: " << params[i] << " result: " << obj->insertLast(params[i]) << endl;
    else if (fn == "deleteFront")
      cout << "result: " << obj->deleteFront() << endl;
    else if (fn == "deleteLast")
      cout << "result: " << obj->deleteLast() << endl;
    else if (fn == "getFront")
      cout << "result: " << obj->getFront() << endl;
    else if (fn == "getRear")
      cout << "result: " << obj->getRear() << endl;
    else if (fn == "isEmpty")
      cout << "result: " << obj->isEmpty() << endl;
    else if (fn == "isFull")
      cout << "result: " << obj->isFull() << endl;
  }
  cout << endl;
  return 0;
}
