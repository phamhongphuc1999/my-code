#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>

using namespace std;

struct TrieNode
{
  TrieNode *children[26];
  string word;
  bool isEnd;

  TrieNode()
  {
    for (int i = 0; i < 26; i++)
      children[i] = NULL;
    word = "";
    isEnd = false;
  }
};

class Trie
{
public:
  TrieNode *root;

  Trie()
  {
    this->root = new TrieNode();
  }

  void insert(string word)
  {
    TrieNode *node = root;
    for (char c : word)
    {
      int idx = c - 'a';
      if (!node->children[idx])
        node->children[idx] = new TrieNode();
      node = node->children[idx];
    }
    node->word = word;
  }

  bool search(string word)
  {
    TrieNode *node = root;
    for (char c : word)
    {
      int index = c - 'a';
      if (node->children[index] == NULL)
        return false;
      node = node->children[index];
    }
    return node->isEnd;
  }

  bool startsWith(string prefix)
  {
    TrieNode *node = root;
    for (char c : prefix)
    {
      int index = c - 'a';
      if (node->children[index] == NULL)
        return false;
      node = node->children[index];
    }
    return true;
  }
};

#endif
