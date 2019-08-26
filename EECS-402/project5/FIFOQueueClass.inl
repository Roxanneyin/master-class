#include <iostream>
using namespace std;
#include "LinkedNodeClass.h"

/*---------------Member functions for FIFOQueueClass---------------*/
template < class T >
FIFOQueueClass< T >::FIFOQueueClass()
{
  head = 0;
  tail = 0;
}

template < class T >
FIFOQueueClass< T >::~FIFOQueueClass()
{
  clear();
}

template < class T >
void FIFOQueueClass< T >::enqueue(
  const T &newItem
  )
{
  LinkedNodeClass< T > *quePtr = head;
  LinkedNodeClass< T > *newNode; 
  if (head == 0)
  {
    newNode = new LinkedNodeClass< T >(0, newItem, 0);
    head = newNode;
    tail = newNode;
  }
  else
  {
    newNode = new LinkedNodeClass< T >(tail, newItem, 0);
    newNode -> setBeforeAndAfterPointers();
    tail = newNode;
  }
}

template < class T >
bool FIFOQueueClass< T >::dequeue(
  T &outItem
  )
{
  bool empty = false;
  LinkedNodeClass< T > *temp = head; //Used to point a node temporarily.

  if (temp == 0)
  {
    empty = true;
  }
  else if (temp -> getNext() == 0)
  {
    outItem = temp -> getValue();
    delete temp;
    head = 0;
    tail = 0;
    temp = 0;
  }
  else
  {
    outItem = temp -> getValue();
    head = temp -> getNext();
    delete temp;
    head -> setPreviousPointerToNull();
    temp = 0;
  }

  return (!empty);
}

template < class T >
void FIFOQueueClass< T >::print() const
{
  LinkedNodeClass< T > *quePtr = head; //Used to go through every element.

  while (quePtr != 0)
  {
    cout << quePtr -> getValue() << " ";
    quePtr = quePtr -> getNext();
  }
  cout << endl;
}

template < class T >
int FIFOQueueClass< T >::getNumElems() const
{
  int queNum = 0;
  LinkedNodeClass< T > *quePtr = head; //Used to go through every element.

  while(quePtr != 0)
  {
    queNum++;
    quePtr = quePtr -> getNext();
  }

  return (queNum);
}

template < class T >
void FIFOQueueClass< T >::clear()
{
  LinkedNodeClass< T > *quePtr = head;
  LinkedNodeClass< T > *temp;

  while(quePtr != 0)
  {
    temp = quePtr;
    quePtr = quePtr -> getNext();
    delete temp;
  }
  head = 0;
  tail = 0;
}