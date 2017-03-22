#include <node.hpp>

unsigned long Node::_numberOfNode = 0;
Node* Node::_zeroTerminal = NULL;

/* for terminal node */
Node::Node(int val) {
  _var = -1;
  _val = val;
  _left = NULL;
  _right = NULL;
}

/* for non-terminal node */
Node::Node(int var, Node* left, Node* right) {
  _var = var;
  _val = -1;
  _left = left;
  _right = right;
}
