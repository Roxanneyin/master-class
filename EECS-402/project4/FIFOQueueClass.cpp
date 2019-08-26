#include <iostream>
using namespace std;
#include "FIFOQueueClass.h"
#include "LinkedNodeClass.h"

/*---------------Member functions for FIFOQueueClass---------------*/
FIFOQueueClass::FIFOQueueClass()
{
  head = 0;
  tail = 0;
}

FIFOQueueClass::~FIFOQueueClass()
{
  clear();
}

void FIFOQueueClass::enqueue(
  const int &newItem
  )
{
  LinkedNodeClass *quePtr = head; //Used to go through every node in the list.
  LinkedNodeClass *newNode;        //Set up a new node containing the value to
                                   //be inserted to the existing sorted list.

  if (head == 0)
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

bool FIFOQueueClass::dequeue(
  int &outItem
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

void FIFOQueueClass::print() const
{
  LinkedNodeClass *quePtr = head; //Used to go through every element.

  while (quePtr != 0)
  {
    cout << quePtr -> getValue() << " ";
    quePtr = quePtr -> getNext();
  }
  cout << endl;
}

int FIFOQueueClass::getNumElems() const
{
  int queNum = 0;
  LinkedNodeClass *quePtr = head; //Used to go through every element.

  while(quePtr != 0)
  {
    queNum++;
    quePtr = quePtr -> getNext();
  }

  return (queNum);
}

void FIFOQueueClass::clear()
{
  LinkedNodeClass *quePtr = head; //Used to go through every element
  LinkedNodeClass *temp;          //Used to point every element temporarliy.

  while(quePtr != 0)
  {
    temp = quePtr;
    quePtr = quePtr -> getNext();
    delete temp;
  }
  head = 0;
  tail = 0;
}