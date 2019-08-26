#ifndef _SIMULATIONCLASS_H_
#define _SIMULATIONCLASS_H_

#include <string>
#include <iostream>
using namespace std;
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "EventClass.h"

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
    
    //Print all stats we have to see what can we get from the simulation.
    void printStats();

    //To tell is the list is empty.
    bool listEmpty();
};

#endif