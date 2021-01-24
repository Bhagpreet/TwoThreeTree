#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree( );
  ~Tree( );
  void insert(const string & word);
  void preOrder( ) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void remove(const string & word);
  bool search (const string & word) const;

private:
  void insertHelper(Node* val, Node* prev, const string & word);
  void split(Node * val, Node * parent, Node* lChild, Node* rChild, const string & word);
  void searchHelper(Node* curr, const string & word, string &) const;
  void postHelper(Node* val) const;
  void inHelper(Node* val) const;
  void preHelper(Node* val) const;
  void destruct(Node* root);
  void remove(Node* val, const string & word);
  void setVals(Node* item, Node* & large, string & middle, const string & word);
  void redistribute(Node* successor, Node* parent);
  Node* inorderSucc(Node* val);
  void fix(Node* successor, Node* parent);
  void merge(Node* val, Node* parent);
  // Add additional functions/variables here
    
};

#endif
