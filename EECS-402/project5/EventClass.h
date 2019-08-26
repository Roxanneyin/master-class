#ifndef _EVENTCLASS_H_
#define _EVENTCLASS_H_

#include <iostream>
using namespace std;

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

#endif