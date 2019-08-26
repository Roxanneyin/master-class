/*This golbal function is to check when openning a file or reading in 
content from a file, there will be something wrong.*/

#ifndef _INFILEVALID_H_
#define _INFILEVALID_H_

#include <iostream>
#include <fstream>
using namespace std;

bool inFileValid(ifstream &inFile, bool readIn);

#endif