/* zdd.cpp */

#include <zdd.hpp>

ZDD::ZDD(std::vector<std::string>& rulelist) {
  _hash = new NHash(1000);

  _hash->insert(-1,0,-1,-1);
  for (unsigned i = 1; i <= rulelist.size(); ++i) {
    std::cout << "R[" << i << "] = " << rulelist[i-1] << std::endl;
    _hash->insert(-1,i,-1,-1);
  }
  
  for (unsigned i = 1; i <= rulelist.size(); ++i) {
    int node = _hash->member(-1,i,-1,-1);
    for (int j = rulelist[i-1].size()-1; j > -1; --j) {
      if (rulelist[i-1][j] == '1')
	node = _hash->insert(j+1,-1,0,node);
      if (rulelist[i-1][j] == '*')
	node = _hash->insert(j+1,-1,node,node);
    }
  }
  
  element* tb = _hash->getTable();
  for (unsigned i = 0; i < 1000; ++i) {
    if (occupied == tb[i].getState())
      std::cout << "id[" << i << "] " << tb[i] << std::endl;
  }
}

int ZDD::getNode(int var, int val, int left, int right) {
  int k;
  
  if (-1 != (k = _hash->member(var, val, left, right))) {
    return k;
  } else {
    return _hash->insert(var, val, left, right);
  }

  return -1;
}
