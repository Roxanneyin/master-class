/*This class is to encode or decode message file into/from an image defined
by ColorImageClass*/

#ifndef _STEGACLASS_H_
#define _STEGACLASS_H_

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include "RowColumnClass.h"
#include "ColorClass.h"
#include "ColorImageClass.h"

class StegaClass
{
private:
    int **message; //An integer from 0 to 7 representing message of 8 colors
    int msgRow, msgCol; //Rows and columns of message file

public:
    StegaClass();

    void setSizeTo(RowColumnClass &inRowcol);
    //Set message size to given row and column number
    bool readMsg(string fileName);
    //Read in message from the message file

    void setToEven(int &num); //Change integer to even number
    void setToOdd(int &num); //Change integer to odd number

    bool encodeColor(int msgVal, ColorClass &inColor);
    //Encode one point on an image given message value
    bool decodeColor(ColorClass &inColor);
    //Decode one point on an image
    bool encodeImg(RowColumnClass &startRowCol, ColorImageClass &inImg);
    //Encode whole image with given start point of message
    bool decodeImg(ColorImageClass &inImg);
    //Decode whole image
};

#endif