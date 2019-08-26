/*This class is to define an object containing information of an image,
including it's rows and columns, also it's RGB value on each pixel*/

#ifndef _COLORIMAGECLASS_H_
#define _COLORIMAGECLASS_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "ColorClass.h"
#include "RowColumnClass.h"

class ColorImageClass
{
private:
    ColorClass **image; //The pointer of pointer of image array
    int imgRow, imgCol; //The row and col number of image
    bool isValidLoc(RowColumnClass &inRowCol);
    //To check if the location is in the range

public:
    ColorImageClass(); //Default ctor
    ColorImageClass(RowColumnClass &inRowCol);

    int getRow();
    int getCol();
    // get values of image row and column

    bool setColorAtLocation(
        RowColumnClass &inRowCol, 
        ColorClass &inColor
        ); //Change the color in specified location and tell if valid
    bool getColorAtLocation(
        RowColumnClass &inRowCol,
        ColorClass &outColor
        ); //Get the RGB values at valid location
        
    void setImgSize(RowColumnClass &inRowCol);
    //Assign cols and rows to the image

    bool readImg(string fileName); //read an image from a file
    bool writeImg(string fileName); //write an image into a file
};

#endif