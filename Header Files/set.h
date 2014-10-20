#ifndef SET_H
#define SET_H

#include "node.h"
#include "hashtable.h"
#include <string>
#include "iterator.h"
using charley::Node;
//using chen::Hashtable;
//using chen::SIZE;


template<class T>
class Set
{
  public:
	  typedef Iterator<T> iterator;
	  Set() {array_size=0; hash_array=NULL; items=0;}
	  Set(int num);
	  void add(T item); 
	  virtual ~Set();
	  bool contains(T target) const;
	  Set<T>* setUnion( const Set<T>& otherSet); 
	  Set<T>* setIntersection( const Set<T>& otherSet);
	  Set<T>& operator =(const Set<T>& other);
	  Set(const Set<T>& other);
	  void output();
	  int size();
	  iterator begin() {return iterator(hash_array, 0);}
	  iterator end() {return iterator(hash_array+array_size, array_size);}
  private:
	  Node<T>** hash_array;
	  int compute(T item) const;
	  int items;
	  int array_size;
};

#endif 