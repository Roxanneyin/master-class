#include <iostream>
using namespace std;
#include "LIFOStackClass.h"
#include "LinkedNodeClass.h"

/*---------------Member functions for LIFOStackClass---------------*/

LIFOStackClass::LIFOStackClass()
{
  head = 0;
  tail = 0;
}

LIFOStackClass::~LIFOStackClass()
{
  clear();
}

void LIFOStackClass::push(
  const int &newItem
  )
{
  LinkedNodeClass *stkPtr = tail; //Used to go through every node in the list.
  LinkedNodeClass *newNode;        //Set up a new node containing the value to
                                   //be inserted to the existing sorted list.

  if (tail == 0)
  {
    newNode = new LinkedNodeClass(0, newItem, 0);
    head = newNode;
    tail = newNode;
  }
  else
  {
    newNode = new LinkedNodeClass(tail, newItem, 0);
    newNode -> setBeforeAndAfterPointers();
    tail = newNode;
  }
}

bool LIFOStackClass::pop(
  int &outItem
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
    outItem = temp -> getValue();
    delete temp;
    head = 0;
    tail = 0;
    temp = 0;
  }
  else
  {
    outItem = temp -> getValue();
    tail = temp -> getPrev();
    delete temp;
    tail -> setNextPointerToNull();
    temp = 0;
  }

  return (!empty);
}

void LIFOStackClass::print() const
{
  LinkedNodeClass *stkPtr = tail; //Used to go through every element.

  while (stkPtr != 0)
  {
    cout << stkPtr -> getValue() << " ";
    stkPtr = stkPtr -> getPrev();
  }
  cout << endl;
}

int LIFOStackClass::getNumElems() const
{
  int stkNum = 0;
  LinkedNodeClass *stkPtr = head; //Used to go through every element.

  while(stkPtr != 0)
  {
    stkNum++;
    stkPtr = stkPtr -> getNext();
  }

  return (stkNum);
}

void LIFOStackClass::clear()
{
  LinkedNodeClass *stkPtr = head; //Used to go through every element
  LinkedNodeClass *temp;          //Used to point every element temporarliy.

  while(stkPtr != 0)
  {
    temp = stkPtr;
    stkPtr = stkPtr -> getNext();
    delete temp;
  }
  head = 0;
  tail = 0;
}