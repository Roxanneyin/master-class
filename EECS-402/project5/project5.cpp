#include <iostream>
#include <string>
using namespace std;

#include "random.h"
#include "SimulationClass.h"
#include "constants.h"

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