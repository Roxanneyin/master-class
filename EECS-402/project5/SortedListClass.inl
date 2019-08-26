#include <iostream>
using namespace std;
#include "LinkedNodeClass.h"

/*---------------Member functions for SortedListClass---------------*/

template < class T >
SortedListClass< T >::SortedListClass()
{
  head = 0;
  tail = 0;
}

template < class T >
SortedListClass< T >::SortedListClass(
  const SortedListClass< T > &rhs
  )
{
  LinkedNodeClass< T > *copyListPtr = rhs.head;
  LinkedNodeClass< T > *temp;
  int num = 0;
    
  
  //This is the condition when rhs is a NULL list.
  if (copyListPtr == 0)
  {
    head = 0;
    tail = 0;
  }

  //When rhs is not a NULL list, we (deeply) copy every element to a new list.
  while (copyListPtr != 0)
    {
      if (num == 0)
      {
        temp = new LinkedNodeClass< T >(0, copyListPtr -> getValue(), 0);
        head = temp;
      }
      else
      {
        temp = new LinkedNodeClass< T >(temp, copyListPtr -> getValue(), 0);
        temp -> setBeforeAndAfterPointers();
      }
      tail = temp;
      copyListPtr = copyListPtr -> getNext();
      num ++;
  }
}

template < class T >
SortedListClass< T >::~SortedListClass()
{
  clear();
}

template < class T >
void SortedListClass< T >::clear()
{
  LinkedNodeClass< T > *listPtr = head; //Used as a pointer to each node when 
                                        //deleting nodes one by one in a list.
  LinkedNodeClass< T > *temp;

  while (listPtr != 0)
  {
    temp = listPtr;
    listPtr = listPtr -> getNext();
    delete temp;
  }

  head = 0;
  tail = 0;
}

template < class T >
void SortedListClass< T >::insertValue(
  const T &valToInsert
  )
{
  LinkedNodeClass< T > *listPtr = head;
  LinkedNodeClass< T > *newNode;

  if (head == 0)
  {
    newNode = new LinkedNodeClass< T >(0, valToInsert, 0);
    head = newNode;
    tail = newNode;
  }
  else if (head -> getValue() > valToInsert)
  {
    newNode = new LinkedNodeClass< T >(0, valToInsert, head);
    newNode -> setBeforeAndAfterPointers();
    head = newNode;
  }
  else if (tail -> getValue() <= valToInsert)
  {
    newNode = new LinkedNodeClass< T >(tail, valToInsert, 0);
    newNode -> setBeforeAndAfterPointers();
    tail = newNode;
  }
  else
  {
    while (listPtr -> getValue() <= valToInsert)
    {
      listPtr = listPtr -> getNext();
    }

    newNode = 
    new LinkedNodeClass< T >(listPtr -> getPrev(), valToInsert, listPtr);
    newNode -> setBeforeAndAfterPointers();
  }
}

template < class T >
void SortedListClass< T >::printForward() const
{
  LinkedNodeClass< T > *listPtr = head;
  
  cout << "Forward List Contents Follow:" << endl;
  while (listPtr != 0)
  {
    cout << "  " << listPtr -> getValue() << endl;
    listPtr = listPtr -> getNext();
  }
  cout << "End Of List Contents" << endl;
}

template < class T >
void SortedListClass< T >::printBackward() const
{
  LinkedNodeClass< T > *listPtr = tail;

  cout << "Backward List Contents Follow:" << endl;
  while (listPtr != 0)
  {
    cout << "  " << listPtr -> getValue() << endl;
    listPtr = listPtr -> getPrev();
  }
  cout << "End Of List Contents" << endl;
}

template < class T >
bool SortedListClass< T >::removeFront(
  T &theVal
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
    theVal = temp -> getValue();
    delete temp;
    head = 0;
    tail = 0;
    temp = 0;
  }
  else
  {
    theVal = temp -> getValue();
    head = temp -> getNext();
    delete temp;
    head -> setPreviousPointerToNull();
    temp = 0;
  }

  return (!empty);
}

template < class T >
bool SortedListClass< T >::removeLast(
  T &theVal
  )
{
  bool empty = false;
  LinkedNodeClass< T > *temp = tail; //Used to point a node temporarily.

  if (temp == 0)
  {
    empty = true;
  }
  else if (temp -> getPrev() == 0)
  {
    theVal = temp -> getValue();
    delete temp;
    head = 0;
    tail = 0;
    temp = 0;
  }
  else
  {
    theVal = temp -> getValue();
    tail = temp -> getPrev();
    delete temp;
    tail -> setNextPointerToNull();
    temp = 0;
  }

  return (!empty);
}

template < class T >
int SortedListClass< T >::getNumElems() const
{
  int listNum = 0;
  LinkedNodeClass< T > *listPtr = head;

  while (listPtr != 0)
  {
    listNum++;
    listPtr = listPtr -> getNext();
  }

  return (listNum);
}

template < class T >
bool SortedListClass< T >::getElemAtIndex(
  const int index,
  T &outVal
  ) const
{
  bool valid = true;
  int count = 0;
  LinkedNodeClass< T > *listPtr = head;

  if ((getNumElems() <= index) || (index < 0))
  {
    valid = false;
  }
  else
  {
    while (count <= index)
    {
      outVal = listPtr -> getValue();
      listPtr = listPtr -> getNext();
      count++;
    }
  }

  return (valid);
}