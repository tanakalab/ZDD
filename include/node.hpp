/* node.hpp */

#ifndef __ZDD_NODE_HPP__
#define __ZDD_NODE_HPP__

#include <iostream>
#include <string>

class Node {
private:
  int var; // variable for non-terminal node
  int val; // value for terminal node
  Node* left;
  Node* right;
};

#endif
