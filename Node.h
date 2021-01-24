#ifndef __NODE_H
#define __NODE_H

#include <string>
#include <iostream>

using namespace std;

class Node {

  friend class Tree;

public:
  Node();
  Node(const string &);

private:

  string small;
  string large;

  Node *left;
  Node *middle;
  Node *right;
  Node *parent;

  // Add additional functions/variables here. Remember, you may not add any
  // Node * or string variables.


};

#endif
