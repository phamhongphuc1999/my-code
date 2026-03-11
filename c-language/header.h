#ifndef HEADER_H
#define HEADER_H

#include <vector>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Node
{
public:
  int val;
  std::vector<Node *> children;

  Node() {}

  Node(int _val)
  {
    val = _val;
  }

  Node(int _val, std::vector<Node *> _children)
  {
    val = _val;
    children = _children;
  }
};

class NextNode
{
public:
  int val;
  NextNode *left;
  NextNode *right;
  NextNode *next;

  NextNode() : val(0), left(NULL), right(NULL), next(NULL) {}

  NextNode(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

  NextNode(int _val, NextNode *_left, NextNode *_right, NextNode *_next)
      : val(_val), left(_left), right(_right), next(_next) {}
};

bool exists(int mask, int index)
{
  return (mask >> index) & 1;
}

int add(int mask, int x)
{
  int result = (1 << x) | mask;
  return result;
}

void subtract(int &mask, int x)
{
  mask &= ~(1 << x);
}

#endif