/* zdd.hpp */

#ifndef __ZDD_ZDD_HPP__
#define __ZDD_ZDD_HPP__

#ifndef __ZDD_HASH_HPP__
#include <hash.hpp>
#endif

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <unordered_set>
#include <unordered_map>

class ZDD {
private:
  unsigned _numberOfNode;
  Hash* _hash;
  std::map< std::pair<int,int>, int> _cache;
  int _osize;
  std::map<int, int> _countCache;
  int _root;
  int getNode(int, int, int, int);
  int topVar(int);
  int topVal(int);
  int getLeft(int);
  int getRight(int);
  int unification(int, int);
public:
  ZDD(char**, int, int);
  ZDD(std::string*, int, int);
  ZDD(std::vector<std::string>&, int, int);
  void print();
  void printSub(int, element*, std::unordered_set<int>*);
  int count(int n);  // count a number of paths to the n terminal node
  int countSub(int, int, element*);
  unsigned getNumberOfNodes();
};

#endif
