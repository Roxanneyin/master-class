#include <iostream>
using namespace std;

#include "isEven.h"
#include "constants.h"

bool isEven(int num)
{
    if (num % 2)
    {
        return false;
    }
    else
    {
        return true;
    }
}