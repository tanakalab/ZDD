/* hash.hpp */

#ifndef __ZDD_HASH_HPP__
#define __ZDD_HASH_HPP__

#include <stdlib.h>
#include <cstdint>
#include <iostream>

enum oed { occupied, empty, deleted };

class element {
private:
  int _var; // terminal nodes _var is (n+1), where n is a number of variables
  int _val; // non terminal nodes _val is -1
  int _left;
  int _right;
  unsigned _rcounter; // number of edges which reference this node. if _rcounter is 0 then this node should be deleted
  enum oed _state;
public:
  element(int, int, int, int);
  element(int, int, int, int, unsigned);
  void setEmpty();
  void setOccupied();
  void setDeleted();
  int getVar();
  int getVal();
  int getLeft();
  int getRight();
  unsigned getCounter();
  void incCounter();
  void decCounter();
  enum oed getState();
  friend std::ostream& operator<<(std::ostream&, const element&);
  void operator=(const element&);
  bool operator==(const element&);
  bool operator!=(const element&);
};

class Hash {
private:
  int _n; // a number of variables
  unsigned _B; // bucket size
  element* _table;
  void initialize();
  int htf(int, int, int, int); // hush function
public:
  Hash(unsigned, int);
  ~Hash();
  int insert(int, int, int, int);
  int insert(int, int, int, int, unsigned);
  void remove(int, int, int, int);
  int member(int, int, int, int);
  element* getTable();
  int topVar(int);
  int topVal(int);
  int getLeft(int);
  int getRight(int);
  unsigned getCounter(int);
  void incCounter(int);
  void decCounter(int);
};

#endif
