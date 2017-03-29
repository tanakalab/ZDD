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

class ZDD {
private:
  Hash* _hash;
  std::map< std::pair<int,int>, int> _cache;
  int _root;
  int getNode(int, int, int, int);
  int topVar(int);
  int topVal(int);
  int getLeft(int);
  int getRight(int);
  int unification(int, int);
public:
  ZDD(char**);
  ZDD(std::string*);
  ZDD(std::vector<std::string>&);
  void print(int, element*, std::unordered_set<int>*);
};

#endif
