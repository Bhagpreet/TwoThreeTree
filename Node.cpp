#include "Node.h"

Node::Node()
: small(""), large(""), left(0), middle(0), right(0), parent(0) {}

Node::Node(const string & word)
: small(word), large(""), left(0), middle(0), right(0), parent(0) {}
