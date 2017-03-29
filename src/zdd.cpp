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
  std::unordered_set<int> *us = new std::unordered_set<int>();

  int node = unification(f[0],f[1]);
  node = unification(node, f[2]);
  node = unification(node, f[3]);
  node = unification(node, f[4]);

  print(node, tb, us);
  // print(f[0], tb, us);
  // us->clear();
  // print(f[1], tb, us);
  delete us;
}

void ZDD::print(int i, element* tb, std::unordered_set<int>* us) {
  if (-1 == i) { return; }
  auto itr = us->find(i);
  if (us->end() != itr) { return; }
  us->insert(i);
  std::cout << "id[" << i << "] " << tb[i] << std::endl;
  print(tb[i].getLeft(), tb, us);
  print(tb[i].getRight(), tb, us);
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

  if (0 == P) { std::cout << "0 == P\n"; return Q; }
  if (0 == Q || P == Q) { std::cout << "0 == Q\n"; return P; }
  if (-1 == topVar(P) && -1 == topVar(Q)) {
    if (P < Q) { return P; }
    else { return Q; }
  }
  auto itr = _cache.find(std::pair<int,int>(P,Q));
  if (_cache.end() != itr) { return itr->second; }
  if ((topVar(P) < topVar(Q) && topVar(P) != -1) || -1 == topVar(Q)) { // node P is farther than node Q
    printf("P < Q : P = %d, Q = %d\n", P, Q);
    R = getNode(topVar(P), topVal(P), unification(getLeft(P),Q), getRight(P));
  }
  else if ((topVar(P) > topVar(Q) && topVar(Q) != -1) || -1 == topVar(P)) {
    printf("P > Q : P = %d, Q = %d\n", P, Q);
    R = getNode(topVar(Q), topVal(Q), unification(P,getLeft(Q)), getRight(Q));
  }
  else if (topVar(P) == topVar(Q)) {
    printf("P == Q : P = %d, Q = %d\n", P, Q);
    R = getNode(topVar(P), topVal(P), unification(getLeft(P),getLeft(Q)), unification(getRight(P),getRight(Q)));
  }
  _cache[std::pair<int,int>(P,Q)] = R;
  
  return R;
}
