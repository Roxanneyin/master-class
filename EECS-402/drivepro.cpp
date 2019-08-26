#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

const string ATTRNAME = "Space Mountain"; //Attractions name
const int SEAT_NUM = 20; //Seats available for a car

const int RIDER = 1, CAR = 2;

const int START_TIME = 0;
const int MIN_RIDER = 0, MAX_RIDER = 100;
const double MAX_PERC = 100; //Maximum number for percentage
const int ARG_NUM = 2;

//The list node class will be the data type for individual nodes of
//a doubly-linked data structure.
template < class T >
class LinkedNodeClass
{
  private:
    LinkedNodeClass *prevNode; //Will point to the node that comes before
                               //this node in the data structure. Will be
                               //NULL if this is the first node.
    T nodeVal;               //The value contained within this node.
    LinkedNodeClass *nextNode; //Will point to the node that comes after
                               //this node in the data structure. Will be
                               //NULL if this is the last node.
  public:
    //The ONLY constructor for the linked node class - it takes in the
    //newly created node's previous pointer, value, and next pointer,
    //and assigns them.
    LinkedNodeClass(
      LinkedNodeClass *inPrev, //Address of node that comes before this one
      const T &inVal,        //Value to be contained in this node
      LinkedNodeClass *inNext  //Address of node that comes after this one
      );

    //Returns the value stored within this node.
    T getValue() const;

    //Returns the address of the node that follows this node.
    LinkedNodeClass* getNext() const;

    //Returns the address of the node that comes before this node.
    LinkedNodeClass* getPrev() const;

    //Sets the object's next node pointer to NULL.
    void setNextPointerToNull();

    //Sets the object's previous node pointer to NULL.
    void setPreviousPointerToNull();

    //This function DOES NOT modify "this" node. Instead, it uses
    //the pointers contained within this node to change the previous
    //and next nodes so that they point to this node appropriately.
    //In other words, if "this" node is set up such that its prevNode
    //pointer points to a node (call it "A"), and "this" node's
    //nextNode pointer points to a node (call it "B"), then calling
    //setBeforeAndAfterPointers results in the node we're calling
    //"A" to be updated so its "nextNode" points to "this" node, and
    //the node we're calling "B" is updated so its "prevNode" points
    //to "this" node, but "this" node itself remains unchanged.
    void setBeforeAndAfterPointers();
};

//The sorted list class does not store any data directly. Instead,
//it contains a collection of LinkedNodeClass objects, each of which
//contains one element.
template < class T >
class SortedListClass
{
  private:
    LinkedNodeClass< T > *head; //Points to the first node in a list, or NULL
                           //if list is empty.
    LinkedNodeClass< T > *tail; //Points to the last node in a list, or NULL
                           //if list is empty.
  public:
    //Default Constructor. Will properly initialize a list to
    //be an empty list, to which values can be added.
    SortedListClass();

    //Copy constructor. Will make a complete (deep) copy of the list, such
    //that one can be changed without affecting the other.
    SortedListClass(
      const SortedListClass< T > &rhs
      );

    //Destructor. Responsible for making sure any dynamic memory
    //associated with an object is freed up when the opject is
    //being destroyed.
    ~SortedListClass();

    //Clears the list to an empty state without resulting in any
    //memory leaks.
    void clear();

    //Allows the user to insert a value into the list. Since this
    //is a sorted list, there is no need to specify where in the list
    //to insert the element. It will insert it in the appropriate
    //location based on the value being inserted. If the node value
    //being inserted is found to be "equal to" one or more node values
    //already in the list, the newly inserted node will be placed AFTER
    //the previously inserted nodes.
    void insertValue(
      const T &valToInsert //The value to insert into the list
      );

    //Prints the contents of the list from head to tail to the screen.
    //Begins with a line reading "Forward List Contents Follow:", then
    //prints one list element per line, indented two spaces, then prints
    //the line "End Of List Contents" to indicate the end of the list.
    void printForward() const;

    //Prints the contents of the list from tail to head to the screen.
    //Begins with a line reading "Backward List Contents Follow:", then
    //prints one list element per line, indented two spaces, then prints
    //the line "End Of List Contents" to indicate the end of the list.
    void printBackward() const;

    //Removes the front item from the list and returns the value that
    //was contained in it via the reference parameter. If the list
    //was empty, the function returns false to indicate failure, and
    //the contents of the reference parameter upon return is undefined.
    //If the list was not empty and the first item was successfully
    //removed, true is returned, and the reference parameter will
    //be set to the item that was removed.
    bool removeFront(
      T &theVal
      );

    //Removes the last item from the list and returns the value that
    //was contained in it via the reference parameter. If the list
    //was empty, the function returns false to indicate failure, and
    //the contents of the reference parameter upon return is undefined.
    //If the list was not empty and the last item was successfully
    //removed, true is returned, and the reference parameter will
    //be set to the item that was removed.
    bool removeLast(
      T &theVal
      );

    //Returns the number of nodes contained in the list.
    int getNumElems() const;

    //Provides the value stored in the node at index provided in the
    //0-based "index" parameter. If the index is out of range, then outVal
    //remains unchanged and false is returned. Otherwise, the function
    //returns true, and the reference parameter outVal will contain
    //a copy of the value at that location.
    bool getElemAtIndex(
      const int index,
      T &outVal
      ) const;
};

template < class T >
class FIFOQueueClass
{
  private:
    LinkedNodeClass< T > *head; //Points to the first node in a queue, or NULL
                           //if queue is empty.
    LinkedNodeClass< T > *tail; //Points to the last node in a queue, or NULL
                           //if queue is empty.
  public:
    //Default Constructor. Will properly initialize a queue to
    //be an empty queue, to which values can be added.
    FIFOQueueClass();

    //Destructor. Responsible for making sure any dynamic memory
    //associated with an object is freed up when the object is
    //being destroyed.
    ~FIFOQueueClass();

    //Inserts the value provided (newItem) into the queue.
    void enqueue(
      const T &newItem
      );

    //Attempts to take the next item out of the queue. If the
    //queue is empty, the function returns false and the state
    //of the reference parameter (outItem) is undefined. If the
    //queue is not empty, the function returns true and outItem
    //becomes a copy of the next item in the queue, which is
    //removed from the data structure.
    bool dequeue(
      T &outItem
      );

    //Prints out the contents of the queue. All printing is done
    //on one line, using a single space to separate values, and a
    //single newline character is printed at the end.
    void print() const;

    //Returns the number of nodes contained in the queue.
    int getNumElems() const;
    
    //Clears the queue to an empty state without resulting in any
    //memory leaks.
    void clear();
};

//This class represents every event, including the type of rider of car,
//also their arriving time.
class EventClass
{
  private:
    int type; //Type of each event
    int time; //arrive time for each event
  public:
    //Default ctor for eventclass.
    EventClass();

    //Ctor that define variables of eventclass when claim.
    EventClass(
      const int &inType,
      const int &inTime
      );

    //Get the type of the event.
    int getType() const;

    //Get the time of the event.
    int getTime() const;

    //Following are three different definitions for three operators.
    bool operator <= (
      const EventClass &rhs
      );

    bool operator > (
      const EventClass &rhs
      );
    
    void operator = (
      const EventClass &rhs
      );
};

class SimulationClass
{
  private:
    int closingTime;
    double riderArrMean, riderArrStd;
    int carArrMin, carArrMax;
    double percSFP, percFP, percSTD;
    int numSFP, numFP, numSTD;

    int seatAval;

    SortedListClass < EventClass > eventList;

    FIFOQueueClass < int > queueSTD;
    FIFOQueueClass < int > queueFP;
    FIFOQueueClass < int > queueSFP;

    int totalSFP, totalFP, totalSTD;
    int totalRider;
    int totalCar;
    int maxSFP, maxFP, maxSTD;

  public:
    SimulationClass();

    //To check if the simulation parameters file can be successfully read.
    bool readPara(
      const string fileName
      );

    //This is to handle each event so that we can finish simulation.
    void handleEvent();

    //This is to schedule next event and add it into the eventlist.
    void scheduleEvent(int nextType, int currentTime);
    void printStats();
    bool listEmpty();
};

//This is called once at the beginning of program execution
//to set the seed of the pseudo-random number generator.
void setSeed(
    const int seedVal
    );

//Returns an integer value from a uniform distribution 
//between the specified min and max values.
int getUniform(
     const int min,
     const int max
     );

//Returns an integer drawn from a normal distribution
//described by the input mean and standard deviation
//values...
int getNormal(
     const double mean,
     const double stdDev
     );

int main(int argc, char *argv[])
{
  int seedVal;
  string paraFileName;
  SimulationClass sim;

  if (argc != ARG_NUM)
    {
      cout << "You should also input simulation parameter file!" << endl;
      cout << "Please input your parameter file name: " << endl;
      cin >> paraFileName;
    }
  else
  {
    cout << "Read simulation parameters from: " << argv[1] << endl;
    paraFileName = argv[1];
  }

  cout << "Please input a seed value: " << endl;
  cin >> seedVal;
  setSeed(seedVal);

  cout << "This is a " << ATTRNAME << " simulation process!" << endl;
  if (sim.readPara(paraFileName))
  {
    cout << "Simulation parameters read successful: Yes" << endl;

    sim.scheduleEvent(RIDER, START_TIME);
    sim.scheduleEvent(CAR, START_TIME);
    while(!sim.listEmpty())
    {
      sim.handleEvent();
    }

    sim.printStats();
  }

  return (0);
}

/*---------------Member functions for LinkedNodeClass---------------*/

template < class T >
LinkedNodeClass< T >::LinkedNodeClass(
  LinkedNodeClass *inPrev,
  const T &inVal,
  LinkedNodeClass *inNext
  )
{
  prevNode = inPrev;
  nodeVal = inVal;
  nextNode = inNext;
}

template < class T >
T LinkedNodeClass< T >::getValue() const
{
  return (nodeVal);
}

template < class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getNext() const
{
  return (nextNode);
}

template < class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getPrev() const
{
  return (prevNode);
}

template < class T >
void LinkedNodeClass< T >::setNextPointerToNull()
{
  nextNode = 0;
}

template < class T >
void LinkedNodeClass< T >::setPreviousPointerToNull()
{
  prevNode = 0;
}

template < class T >
void LinkedNodeClass< T >::setBeforeAndAfterPointers()
{
  if (prevNode != 0)
  {
    prevNode -> nextNode = this;
  }
  if (nextNode != 0)
  {
    nextNode -> prevNode = this;
  }
}

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

/*---------------Member functions for EventClass---------------*/

EventClass::EventClass()
{
  ;
}

EventClass::EventClass(
  const int &inType,
  const int &inTime
  )
{
  type = inType;
  time = inTime;
}

int EventClass::getType() const
{
  return (type);
}

int EventClass::getTime() const
{
  return (time);
}

bool EventClass::operator <= (
  const EventClass &rhs
  )
{
  return (time <= rhs.time);
}

bool EventClass::operator > (
  const EventClass &rhs
  )
{
  return (time > rhs.time);
}

void EventClass::operator = (
  const EventClass &rhs
  )
{
  type = rhs.type;
  time = rhs.time;
}

/*---------------Member functions for SimulationClass---------------*/

SimulationClass::SimulationClass()
{
  closingTime = 0;
  riderArrMean = 0, riderArrStd = 0;
  carArrMin = 0, carArrMax = 0;
  percSFP = 0, percFP = 0, percSTD = 0;
  numSFP = 0, numFP = 0, numSTD = 0;

  seatAval = SEAT_NUM;

  totalSFP = 0, totalFP = 0, totalSTD = 0;
  totalRider = 0;
  totalCar = 0;
  maxSFP = 0, maxFP = 0, maxSTD = 0;
}

bool SimulationClass::readPara(
  const string fileName
  )
{
  ifstream inFile;

  inFile.open(fileName.c_str());
  if (inFile.fail())
  {
    cout << "Unable to open input file." << endl;
    return false;
  }

  inFile >> closingTime;
  inFile >> riderArrMean >> riderArrStd;
  inFile >> carArrMin >> carArrMax;
  inFile >> percSFP >> percFP;
  inFile >> numSFP >> numFP;

  inFile.close();

  percSTD = MAX_PERC - percSFP - percFP;
  numSTD = seatAval - numSFP - numFP;

  return true;
}

void SimulationClass::handleEvent()
{
  EventClass event;
  int nextTime, nextType;

  eventList.removeFront(event);
  if (event.getType() == RIDER)
  {
    totalRider++;
    cout << "A rider arrive at time: " << event.getTime() << endl;

    int riderProb = getUniform(MIN_RIDER, MAX_RIDER);
    if (riderProb <= percSFP)
    {
      totalSFP++;
      queueSFP.enqueue(event.getTime());
      cout << "A SFP rider comes! Now there are "
      << queueSFP.getNumElems()
      << " people on the SFP line."
      << endl;
      if (queueSFP.getNumElems() >= maxSFP)
      {
        maxSFP = queueSFP.getNumElems();
      }
    }
    else if (riderProb <= (percSFP + percFP))
    {
      totalFP++;
      queueFP.enqueue(event.getTime());
      cout << "A FP rider comes! Now there are "
      << queueFP.getNumElems()
      << " people on the FP line."
      << endl;
      if (queueFP.getNumElems() >= maxFP)
      {
        maxFP = queueFP.getNumElems();
      }
    }
    else
    {
      totalSTD++;
      queueSTD.enqueue(event.getTime());
      cout << "A STD rider comes! Now there are "
      << queueSTD.getNumElems()
      << " people on the STD line."
      << endl;
      if (queueSTD.getNumElems() >= maxSTD)
      {
        maxSTD = queueSTD.getNumElems();
      }
    }

    scheduleEvent(RIDER, event.getTime());
  }
  else if (event.getType() == CAR)
  {
    totalCar++;
    cout << "A car arrive at time: " << event.getTime() << endl;

    int currentSeat = seatAval;
    int riderOnCar;
    if (queueSFP.getNumElems() <= numSFP)
    {
      while (queueSFP.dequeue(riderOnCar))
      {
        currentSeat--;
      }
    }
    else
    {
      currentSeat -= numSFP;
      for (int i = 0; i < numSFP; i++)
      {
        queueSFP.dequeue(riderOnCar);
      }
    }

    if (queueFP.getNumElems() <= numFP)
    {
      while (queueFP.dequeue(riderOnCar))
      {
        currentSeat--;
      }
    }
    else
    {
      currentSeat -= numFP;
      for (int i = 0; i < numFP; i++)
      {
        queueFP.dequeue(riderOnCar);
      }
    }

    if (queueSTD.getNumElems() <= numSTD)
    {
      while (queueSTD.dequeue(riderOnCar))
      {
        currentSeat--;
      }
    }
    else
    {
      currentSeat -= numSTD;
      for (int i = 0; i < numSTD; i++)
      {
        queueFP.dequeue(riderOnCar);
      }
    }

    while (currentSeat && queueSFP.getNumElems() != 0)
    {
      currentSeat--;
      queueSFP.dequeue(riderOnCar);
    }

    while (currentSeat && queueFP.getNumElems() != 0)
    {
      currentSeat--;
      queueFP.dequeue(riderOnCar);
    }
    while (currentSeat && queueSTD.getNumElems() != 0)
    {
      currentSeat--;
      queueSTD.dequeue(riderOnCar);
    }

    cout << "This car have "
    << seatAval - currentSeat
    << " riders on the car."
    << endl;

    scheduleEvent(CAR, event.getTime());
  }
  else
  {
    cout << "Something wrong happened when handle an event!" << endl;
  }
}

void SimulationClass::scheduleEvent(int nextType, int currentTime)
{
  if (nextType == RIDER)
  {
    int nextTime = currentTime + getNormal(riderArrMean, riderArrStd);
    if (nextTime < closingTime)
    {
      EventClass nextEvent(nextType, nextTime);

      eventList.insertValue(nextEvent);
    }
  }
  else if (nextType == CAR)
  {
    int nextTime = currentTime + getUniform(carArrMin, carArrMax);

    if ((queueSFP.getNumElems()
      || queueFP.getNumElems()
      || queueSTD.getNumElems()
      || eventList.getNumElems())
      || (currentTime < closingTime))
    {
      EventClass nextEvent(nextType, nextTime);

      eventList.insertValue(nextEvent);
    }
  }
  else
  {
    cout << "Something wrong happened when schedule next Event!" << endl;
  }
}

void SimulationClass::printStats()
{
  cout << "Total rider number is: "
  << totalRider << endl;
  cout << "Total SFP rider number is: "
  << totalSFP << endl;
  cout << "Total FP rider number is: "
  << totalFP << endl;
  cout << "Total STD rider number is: "
  << totalSTD << endl;
  cout << "Total car number is: "
  << totalCar << endl;
  cout << "The max length for SFP queue is: "
  << maxSFP << endl;
  cout << "The max length for FP queue is: "
  << maxFP << endl;
  cout << "The max length for STD queue is: "
  << maxSTD << endl; 
  cout << "Average of every car containing riders is: "
  << totalRider / double(totalCar) << endl;
  cout << "The average of car occupancy is: "
  << totalRider / double(totalCar) / seatAval * MAX_PERC
  << "%" << endl;
}

bool SimulationClass::listEmpty()
{
  return (eventList.getNumElems() == 0);
}

/*---------------Global functions for random number---------------*/

void setSeed(
    const int seedVal
    )
{
  srand(seedVal);
}

int getUniform(
     const int min,
     const int max
     )
{
  int uniRand;
  uniRand = rand() % ((max + 1) - min) + min;
  return (uniRand);
}

int getNormal(
     const double mean,
     const double stdDev
     )
{
  const int NUM_UNIFORM = 12;
  const int MAX = 1000;
  const double ORIGINAL_MEAN = NUM_UNIFORM * 0.5;
  double sum;
  int i;
  double standardNormal;
  double newNormal;
  int uni;

  sum = 0;
  for (i = 0; i < NUM_UNIFORM; i++)
  {
    uni = rand() % (MAX + 1);
    sum += uni;
  }
  sum = sum / MAX;
  standardNormal = sum - ORIGINAL_MEAN;
  newNormal = mean + stdDev * standardNormal;
  if (newNormal < 0)
  {
    newNormal *= - 1;
  }
  return ((int)newNormal);
}