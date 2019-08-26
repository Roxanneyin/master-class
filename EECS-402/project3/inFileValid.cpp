#include <iostream>
#include <fstream>
using namespace std;

#include "inFileValid.h"
#include "constants.h"

bool inFileValid(ifstream &inFile, bool readIn)
{
    if (readIn)
    {
        if (inFile.fail() || inFile.eof())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        if (inFile.fail())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}