/* zdd.cpp */

#include <zdd.hpp>

ZDD::ZDD(std::vector<std::string>& rulelist) {
  _hash = new Hash(1000);

  std::vector<int> f;
  
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
    f.push_back(node);
  }
  
  element* tb = _hash->getTable();
  print(f[1], tb);
  unification(f[0],f[1]);
}

void ZDD::print(int i, element* tb) {
  if (-1 == i) { return; }
  std::cout << "id[" << i << "] " << tb[i] << std::endl;
  print(tb[i].getLeft(), tb);
  print(tb[i].getRight(), tb);
}

int ZDD::topVar(int i) { return _hash->topVar(i); }
int ZDD::topVal(int i) { return _hash->topVal(i); }
int ZDD::getLeft(int i) { return _hash->getLeft(i); }
int ZDD::getRight(int i) { return _hash->getRight(i); }


/* Warning!! getNode of BDDs is different from one of ZDDs. */
int ZDD::getNode(int var, int val, int left, int right) {
  if (0 == right) { return left; }

  int P = _hash->member(var, val, left, right);
  if (-1 != P) { return P; }
  P = _hash->insert(var, val, left, right);
  return P;
}

int ZDD::unification(int P, int Q) {
  int R;

  if (0 == P) { return Q; }
  if (0 == Q || P == Q) { return P; }
  if (-1 == topVar(P) && -1 == topVar(Q)) {
    if (topVal(P) < topVal(Q)) { return topVal(P); }
    else topVal(Q);
  }
  auto itr = _cache.find(std::pair<int,int>(P,Q));
  if (_cache.end() != itr) { return itr->second; }
  if (topVar(P) < topVar(Q) || -1 == topVar(P))
    R = getNode(topVar(P), topVal(P), unification(getLeft(P),Q), getRight(P));
  if (topVar(P) > topVar(Q) || -1 == topVar(Q))
    R = getNode(topVar(Q), topVal(Q), unification(P,getLeft(Q)), getRight(Q));
  if (topVar(P) == topVar(Q))
    R = getNode(topVar(P), topVal(P), unification(getLeft(P),getLeft(Q)), unification(getRight(P),getRight(Q)));
  _cache[std::pair<int,int>(P,Q)] = R;
  
  return R;
}
