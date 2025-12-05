#include <string>
#include <stack>
#include <iostream>

using namespace std;

int countCollisions(string directions)
{
  stack<char> st;
  int result = 0;
  for (char c : directions)
  {
    if (st.size() == 0)
    {
      if (c != 'L')
        st.push(c);
    }
    else
    {
      char pre = st.top();
      if ((pre == 'S' || pre == 'L') && c == 'L')
      {
        result += 1;
        st.push(c);
      }
      else if (pre == 'R' && c == 'L')
      {
        result += 2;
        st.pop();
        while (st.size() > 0 && st.top() == 'R')
        {
          result += 1;
          st.pop();
        }
        st.push(c);
      }
      else if (c == 'R')
        st.push(c);
      else
      {
        while (st.size() > 0 && st.top() == 'R')
        {
          result += 1;
          st.pop();
        }
        st.push(c);
      }
    }
  }
  return result;
}

int main()
{
  int result = countCollisions("SSRSSRLLRSLLRSRSSRLRRRRLLRRLSSRR");
  cout << result << endl;
}