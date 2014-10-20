#ifndef ITERATOR_H
#define ITERATOR_H


#include "node.h"

template <class T>
class Iterator
{
  public:
	  Iterator(): current(NULL), counter(0) {}
	  Iterator(Node<T>** ptr, int pos): current(ptr), counter(pos) {}
	  Iterator<T>& operator ++();
	
	  Iterator<T>& operator ++(int);

	  bool operator ==(const Iterator<T>& right_side);

	  bool operator !=(const Iterator<T>& right_side);
	  Node<T>* operator *();
  private:
	  Node<T>** current;
	  int counter;
};
#endif //ITERATOR_H

