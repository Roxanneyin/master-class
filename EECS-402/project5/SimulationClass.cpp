#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include "SimulationClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "random.h"
#include "EventClass.h"
#include "constants.h"

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