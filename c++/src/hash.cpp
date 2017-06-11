/* hash.cpp */

#include <hash.hpp>

std::ostream& operator<<(std::ostream& os, const element& e) {
  os << "var = " << e._var << ", val = " << e._val << ", left = " << e._left << ", right = " << e._right << ", state = " << e._state;
  return os;
}

void element::operator=(const element& r) {
  _var = r._var;
  _val = r._val;
  _left = r._left;
  _right = r._right;
  _state = r._state;
}

bool element::operator==(const element& r) {
  if (_var != r._var) { return false; }
  if (_val != r._val) { return false; }
  if (_left != r._left) { return false; }
  if (_right != r._right) { return false; }
  return true;
}

bool element::operator!=(const element& other) {
  return !(*this == other);
}

element::element(int var, int val, int left, int right) {
  _var = var;
  _val = val;
  _left = left;
  _right = right;
}

void element::setEmpty() { _state = empty; }
void element::setOccupied() { _state = occupied; }
void element::setDeleted() { _state = deleted; }
int element::getVar() { return _var; }
int element::getVal() { return _val; }
int element::getLeft() { return _left; }
int element::getRight() { return _right; }
enum oed element::getState() { return _state; }

Hash::Hash(unsigned B, int n) {
  _B = B;
  _n = n;
  initialize();
}

Hash::~Hash() { free(_table); }

void Hash::initialize() {
  _table = (element*)malloc(sizeof(element)*_B);
  for (unsigned i = 0; i < _B; ++i) { _table[i].setEmpty(); }
}

int Hash::htf(int var, int val, int left, int right) {
  if (var == _n+1) { return val; }
  
  int h = 0;
  h += var;
  h += left;
  h += right;
  
  return h % _B;
}

int Hash::insert(int var, int val, int left, int right) {
  /* add element (var, val, left, right) to Hash Table _table */
  int i, k, found = -1;
  enum oed cstate;
  element e(var, val, left, right);
  
  k = i = htf(var, val, left, right);
  do {
    cstate = _table[k].getState();
    if (cstate == empty || cstate == deleted)
      { if (found < 0) { found = k; } }
    else 
      { if (e == _table[i]) { return -1; } }

    k = (k+1)%_B;
  } while (cstate != empty && k != i);

  if (found < 0) {
    printf("Error: Dictionary is full.\n");
    std::cout << "i = " << k << ", " << e << std::endl;
    exit(1);
  }
  _table[found] = e;
  _table[found].setOccupied();

  return found;
}

void Hash::remove(int var, int val, int left, int right) {
  /* delete the element (var, val, left, right) from Hash Table _table */
  int i, k;
  enum oed cstate;
  element e(var, val, left, right);
  
  k = i = htf(var, val, left, right);
  do {
    cstate = _table[k].getState();
    if (cstate == occupied) 
      { if (e == _table[k]) { _table[k].setDeleted(); return;} }
    k = (k+1) % _B;
  } while (cstate != empty && k != i);
  return;
}

int Hash::member(int var, int val, int left, int right) {
  int i, k;
  enum oed cstate;
  element e(var, val, left, right);

  k = i = htf(var, val, left, right);
  do {
    cstate = _table[k].getState();
    if (cstate == occupied)
      { if (e == _table[k]) { return k; } }
    k = (k+1) % _B;
  } while (cstate != empty && k != i);
  
  return -1;
}

element* Hash::getTable() { return _table; }
int Hash::topVar(int i) { return _table[i].getVar(); }
int Hash::topVal(int i) { return _table[i].getVal(); }
int Hash::getLeft(int i) { return _table[i].getLeft(); }
int Hash::getRight(int i) { return _table[i].getRight(); }
