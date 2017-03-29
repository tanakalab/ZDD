/* hash.hpp */

#ifndef __ZDD_NHASH_HPP__
#define __ZDD_NHASH_HPP__

#include <stdlib.h>
#include <cstdint>
#include <iostream>

enum oed { occupied, empty, deleted };

class element {
private:
  int _var;
  int _val;
  int _left;
  int _right;
  enum oed _state;
public:
  element(int, int, int, int);
  void setEmpty();
  void setOccupied();
  void setDeleted();
  int getVar();
  int getVal();
  int getLeft();
  int getRight();
  enum oed getState();
  friend std::ostream& operator<<(std::ostream&, const element&);
  void operator=(const element&);
  bool operator==(const element&);
  bool operator!=(const element&);
};

class NHash {
private:
  unsigned _B; // bucket size
  element* _table;
  void initialize();
  int htf(int, int, int, int); // hush function
public:
  NHash(unsigned);
  ~NHash();
  int insert(int, int, int, int);
  void remove(int, int, int, int);
  int member(int, int, int, int);
  element* getTable();
};

#endif
