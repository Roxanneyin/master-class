#include <iostream>
using namespace std;
#include "EventClass.h"

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