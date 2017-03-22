/* node.hpp */

#ifndef __ZDD_NODE_HPP__
#define __ZDD_NODE_HPP__

#include <iostream>
#include <string>

class Node {
private:
  static unsigned long _numberOfNode;
  static Node* _zeroTerminal;
  int _var; // variable for non-terminal node
  int _val; // value for terminal node
  Node* _left;
  Node* _right;
public:
  Node(int);               // for terminal node
  Node(int, Node*, Node*); // for non-terminal node
};

#endif
