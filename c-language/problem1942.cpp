#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

/*https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/description/*/
int smallestChair(vector<vector<int>> &times, int targetFriend)
{
  vector<int> visitTimes;
  vector<vector<int>> leaveTimes;
  int counter = 0;
  int targetVisitTime = -1;
  for (vector<int> time : times)
  {
    visitTimes.push_back(time[0]);
    leaveTimes.push_back(time);
    if (counter == targetFriend)
      targetVisitTime = time[0];
    counter++;
  }
  unordered_map<int, int> umap;
  priority_queue<int, vector<int>, greater<int>> chairs;
  sort(visitTimes.begin(), visitTimes.end());
  sort(leaveTimes.begin(), leaveTimes.end(), [](vector<int> &item1, vector<int> &item2)
       { return item1[1] < item2[1]; });
  int visitCounter = 0;
  int leaveCounter = 0;
  chairs.push(0);
  while (targetVisitTime >= leaveTimes[leaveCounter][1] || targetVisitTime > visitTimes[visitCounter])
  {
    int _visit = visitTimes[visitCounter];
    int _leave = leaveTimes[leaveCounter][1];
    if (_visit < _leave)
    {
      visitCounter++;
      int chair = chairs.top();
      chairs.pop();
      if (chairs.empty())
        chairs.push(chair + 1);
      umap[_visit] = chair;
    }
    else
    {
      int chair = umap[leaveTimes[leaveCounter][0]];
      chairs.push(chair);
      leaveCounter++;
    }
  }
  return chairs.top();
}

int main()
{
  vector<int> p1{3, 10};
  vector<int> p2{1, 10};
  vector<int> p3{2, 20};
  vector<int> p4{11, 13};
  vector<vector<int>> p{p1, p2, p3, p4};
  cout << smallestChair(p, 3) << endl;
  return 0;
}
