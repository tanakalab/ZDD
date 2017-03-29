/* zdd.hpp */

#ifndef __ZDD_ZDD_HPP__
#define __ZDD_ZDD_HPP__

#ifndef __ZDD_NHASH_HPP__
#include <nhash.hpp>
#endif

#include <vector>
#include <string>
#include <iostream>

class ZDD {
private:
  NHash* _hash;
  int _root;
  int getNode(int, int, int, int);
public:
  ZDD(char**);
  ZDD(std::string*);
  ZDD(std::vector<std::string>&);
};

#endif
