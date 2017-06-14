/* zdd.cpp */

#include <zdd.hpp>

ZDD::ZDD(std::vector<std::string>& rulelist, int hsize, int osize) {
  _n = rulelist[0].size();
  _hash = new Hash(hsize, _n);
  _osize = osize;
  std::vector<int> f;

  _hash->insert(_n+1,0,-1,-1,1);
  for (unsigned i = 1; i <= rulelist.size(); ++i) 
    _hash->insert(_n+1,i,-1,-1,1);
  
  for (unsigned i = 1; i <= rulelist.size(); ++i)
    f.push_back(makeZDDforRule(i,rulelist[i-1]));

  int node = f[0];
  for (unsigned i = 1; i < rulelist.size(); ++i)
    node = unification(node,f[i]);
  _root = node;
}

int ZDD::topVar(int i) { return _hash->topVar(i); }
int ZDD::topVal(int i) { return _hash->topVal(i); }
int ZDD::getLeft(int i) { return _hash->getLeft(i); }
int ZDD::getRight(int i) { return _hash->getRight(i); }
unsigned ZDD::getCounter(int i) { return _hash->getCounter(i); }
void ZDD::incCounter(int i) { _hash->incCounter(i); }
void ZDD::decCounter(int i) { _hash->decCounter(i); }

/* Warning!! getNode of BDDs is different from one of ZDDs. */
int ZDD::getNode(int var, int val, int left, int right) {
  if (0 == right) { return left; }

  int P = _hash->member(var, val, left, right);
  if (-1 != P) {
    incCounter(P);
    return P;
  }
  P = _hash->insert(var, val, left, right, 1);
  return P;
}

int ZDD::makeZDDforRule(int node, std::string& rule) {
  // std::cout << node << ", " << rule << std::endl;
  for (int j = rule.size()-1; j > -1; --j) {
    if (rule[j] == '1') {
      node = _hash->insert(j+1,-1,0,node,1);
      incCounter(0);
    }
    if (rule[j] == '*') { node = _hash->insert(j+1,-1,node,node,2);}
  }
  return node;
}

int ZDD::unification(int P, int Q) {
  int R;

  if (0 == P) { // std::cout << "0 == P\n";
    return Q; }
  if (0 == Q || P == Q) { // std::cout << "0 == Q\n";
    return P; }
  if (P == _n+1 && Q == _n+1) {
    if (P < Q) { return P; }
    else { return Q; }
  }
  auto itr = _cache.find(std::pair<int,int>(P,Q));
  if (_cache.end() != itr) { return itr->second; }
  if (topVar(P) < topVar(Q)) {
    // node P is farther than node Q
    // printf("P < Q : P = %d, Q = %d\n", P, Q);
    R = getNode(topVar(P), topVal(P), unification(getLeft(P),Q), getRight(P));
  }
  else if (topVar(P) > topVar(Q)) {
    // printf("P > Q : P = %d, Q = %d\n", P, Q);
    R = getNode(topVar(Q), topVal(Q), unification(P,getLeft(Q)), getRight(Q));
  }
  else if (topVar(P) == topVar(Q)) {
    // printf("P == Q : P = %d, Q = %d\n", P, Q);
    R = getNode(topVar(P), topVal(P), unification(getLeft(P),getLeft(Q)), unification(getRight(P),getRight(Q)));
  }
  _cache[std::pair<int,int>(P,Q)] = R;
  if (_cache.size() > _osize) { _cache.clear(); }
  
  return R;
}

int ZDD::count(int n) {
  int m = countSub(n, _root, _hash->getTable());
  _countCache.clear();
  return m;
}

int ZDD::countSub(int n, int P, element* tb) {
  if (0 == P) { return 0; }
  else if (n == P) { return 1; }
  if (tb[P].getVal() != -1) { return 0; }
  auto itr = _countCache.find(P);
  if (_countCache.end() != itr) { return itr->second; }
  int sum = countSub(n, getLeft(P), tb) + countSub(n, getRight(P), tb);
  _countCache[P] = sum;
  return sum;
}

std::list<std::string>* ZDD::getMatchHeaders(int n) {
  std::map<int, std::list<std::string>>* cache = new std::map<int, std::list<std::string>>();
  std::list<std::string>* h = getMatchHeadersSub(n, _root, 1, cache);
  std::list<std::string>* headers = new std::list<std::string>();

  for (auto p : *h) { headers->push_back(p); }

  return headers;
}

std::list<std::string>* ZDD::getMatchHeadersSub(int n, int P, int j, std::map<int, std::list<std::string>>* cache) {
  std::list<std::string>* headers = new std::list<std::string>();

  return headers;
}

void ZDD::print() {
  std::unordered_set<int>* us = new std::unordered_set<int>();
  printSub(_root, _hash->getTable(), us);
  delete us;
}

void ZDD::printSub(int i, element* tb, std::unordered_set<int>* us) {
  if (-1 == i) { return; }
  auto itr = us->find(i);
  if (us->end() != itr) { return; }
  us->insert(i);
  std::cout << "id[" << i << "] " << tb[i] << std::endl;
  printSub(tb[i].getLeft(), tb, us);
  printSub(tb[i].getRight(), tb, us);
}

unsigned ZDD::getNumberOfNodes() {
  std::unordered_set<int>* us = new std::unordered_set<int>();
  unsigned num = getNumberOfNodesSub(_root, us);
  delete us;
  return num;
}

unsigned ZDD::getNumberOfNodesSub(int P, std::unordered_set<int>* us) {
  if (-1 == P) { return 0; }
  auto itr = us->find(P);
  if (us->end() != itr) { return 0; }
  us->insert(P);
  
  return 1 + getNumberOfNodesSub(getLeft(P),us) + getNumberOfNodesSub(getRight(P),us);
}
