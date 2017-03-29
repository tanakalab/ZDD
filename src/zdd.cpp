/* zdd.cpp */

#include <zdd.hpp>

ZDD::ZDD(std::vector<std::string>& rulelist) {
  _hash = new NHash(50);

  _hash->insert(-1,0,-1,-1);
  for (unsigned i = 1; i <= rulelist.size(); ++i) {
    std::cout << "R[" << i << "] = " << rulelist[i-1] << std::endl;
    _hash->insert(-1,i,-1,-1);
  }

  _hash->remove(-1,0,-1,-1);
  element* tb = _hash->getTable();
  for (unsigned i = 0; i < 50; ++i)
    std::cout << tb[i] << std::endl;
}

int ZDD::getNode(int var, int val, int left, int right) {
  int k;
  
  if (left == right) { return left; }
  if (-1 != (k = _hash->member(var, val, left, right))) {
    return k;
  } else {
    return _hash->insert(var, val, left, right);
  }

  return -1;
}
