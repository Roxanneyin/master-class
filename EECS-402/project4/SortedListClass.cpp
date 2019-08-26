#include <iostream>
using namespace std;
#include "SortedListClass.h"
#include "LinkedNodeClass.h"

/*---------------Member functions for SortedListClass---------------*/

SortedListClass::SortedListClass()
{
  head = 0;
  tail = 0;
}

SortedListClass::SortedListClass(
  const SortedListClass &rhs
  )
{
  LinkedNodeClass *copyListPtr = rhs.head; //This pointer is to go through
                                           //every element of list rhs again
                                           //so that we can copy it to the list
                                           //calling this ctor function.
  LinkedNodeClass *temp;                   //For new list storing temp pointers
  int num = 0;                             //This is used to count element
                                           //number in rhs list.
    
  
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
        temp = new LinkedNodeClass(0, copyListPtr -> getValue(), 0);
        head = temp;
      }
      else
      {
        temp = new LinkedNodeClass(temp, copyListPtr -> getValue(), 0);
        temp -> setBeforeAndAfterPointers();
      }
      tail = temp;
      copyListPtr = copyListPtr -> getNext();
      num ++;
  }
}

SortedListClass::~SortedListClass()
{
  clear();
}

void SortedListClass::clear()
{
  LinkedNodeClass *listPtr = head; //Used as a pointer to each node when 
                                   //deleting nodes one by one in a list.
  LinkedNodeClass *temp;           //Used as a temp pointer to clear a list.

  while (listPtr != 0)
  {
    temp = listPtr;
    listPtr = listPtr -> getNext();
    delete temp;
  }

  head = 0;
  tail = 0;
}

void SortedListClass::insertValue(
  const int &valToInsert
  )
{
  LinkedNodeClass *listPtr = head; //Used to go through every node in the list.
  LinkedNodeClass *newNode;        //Set up a new node containing the value to
                                   //be inserted to the existing sorted list.

  if (head == 0)
  {
    newNode = new LinkedNodeClass(0, valToInsert, 0);
    head = newNode;
    tail = newNode;
  }
  else if (head -> getValue() > valToInsert)
  {
    newNode = new LinkedNodeClass(0, valToInsert, head);
    newNode -> setBeforeAndAfterPointers();
    head = newNode;
  }
  else if (tail -> getValue() <= valToInsert)
  {
    newNode = new LinkedNodeClass(tail, valToInsert, 0);
    newNode -> setBeforeAndAfterPointers();
    tail = newNode;
  }
  else
  {
    while (listPtr -> getValue() <= valToInsert)
    {
      listPtr = listPtr -> getNext();
    }

    newNode = new LinkedNodeClass(listPtr -> getPrev(), valToInsert, listPtr);
    newNode -> setBeforeAndAfterPointers();
  }
}

void SortedListClass::printForward() const
{
  LinkedNodeClass *listPtr = head; //Used to go through every node in the list.
  
  cout << "Forward List Contents Follow:" << endl;
  while (listPtr != 0)
  {
    cout << "  " << listPtr -> getValue() << endl;
    listPtr = listPtr -> getNext();
  }
  cout << "End Of List Contents" << endl;
}

void SortedListClass::printBackward() const
{
  LinkedNodeClass *listPtr = tail; //Used to go through every node in the list.

  cout << "Backward List Contents Follow:" << endl;
  while (listPtr != 0)
  {
    cout << "  " << listPtr -> getValue() << endl;
    listPtr = listPtr -> getPrev();
  }
  cout << "End Of List Contents" << endl;
}

bool SortedListClass::removeFront(
  int &theVal
  )
{
  bool empty = false;
  LinkedNodeClass *temp = head; //Used to point a node temporarily.

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

bool SortedListClass::removeLast(
  int &theVal
  )
{
  bool empty = false;
  LinkedNodeClass *temp = tail; //Used to point a node temporarily.

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

int SortedListClass::getNumElems() const
{
  int listNum = 0;
  LinkedNodeClass *listPtr = head; //Used to go through every node in the list.

  while (listPtr != 0)
  {
    listNum++;
    listPtr = listPtr -> getNext();
  }

  return (listNum);
}

bool SortedListClass::getElemAtIndex(
  const int index,
  int &outVal
  ) const
{
  bool valid = true;
  int count = 0;
  LinkedNodeClass *listPtr = head; //Used to go through every node in the list.

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