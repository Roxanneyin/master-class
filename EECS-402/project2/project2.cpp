#include <iostream>
using namespace std;

/* Program Header - Yuan Yin, 
This is a program to define three classes to represent 
colors, images and locations within an image, 02-07-2019 */

const int FULL = 1000; //The full(maximum) value of a color
const int EMPTY = 0; //The minimum value of a color
const int DEFAULT = -99999; //Initialization to col and row
const int ROW = 10, COL = 18; //Row and Col of the array

class ColorClass
{
private:
    int red; //Red color
    int green; //Greed color
    int blue; //Blue color
    bool clip(int &color); //Out of range value clip into range
    bool colorChanged(
        int &inRed, 
        int &inGreen, 
        int &inBlue
        ); // Tell if the RGB color has changed
  
public:
    ColorClass(); //This is a default ctor function
    ColorClass(
        int inRed,
        int inGreen,
        int inBlue
        ); //This is a value ctor function
    void setToBlack(); //Set RGB into color black
    void setToRed(); //Set RGB into color red
    void setToGreen(); //Set RGB into color green
    void setToBlue(); //Set RGB into color blue
    void setToWhite(); //Set RGB into color white
    bool setTo(
        int inRed,
        int inGreen,
        int inBlue
        ); //Set RGB value as input within range
    bool setTo(ColorClass &inColor); //Set all color to same value
    bool addColor(ColorClass &rhs); //Add RGB value to color object
    bool subtractColor(ColorClass &rhs); //Subtract value to color
    bool adjustBrightness(double adjFactor); //Adjust brightness
    void printComponentValues(); //Print RGB values
};

class RowColumnClass
{
private:
    int row; //Row location
    int col; //Column location

public:
    RowColumnClass(); //default ctor
    RowColumnClass(int inRow, int inCol); //value ctor
    void setRowCol(int inRow, int inCol); //Set row and col values
    void setRow(int inRow); //Set row value
    void setCol(int inCol); //Set col value
    int getRow(); //Return row value
    int getCol(); //Return col value
    void addRowColTo(RowColumnClass &inRowCol); //Add row and col to it
    void printRowCol(); //Print row and col values
};

class ColorImageClass
{
private:
    ColorClass image[ROW][COL]; //The image array
    bool isValidLoc(RowColumnClass &inRowCol);
    //To check if the location is in the range

public:
    ColorImageClass(); //Default ctor
    void initializeTo(ColorClass &inColor); //Initialize the image by input
    bool addImageTo(ColorImageClass &rhsImg); //Add RGB value to each pixel
    bool addImages(int numImgsToAdd, ColorImageClass imagesToAdd[]);
    //Set images with the sum of all inputs
    bool setColorAtLocation(
        RowColumnClass &inRowCol, 
        ColorClass &inColor
        ); //Change the color in specified location and tell if valid
    bool getColorAtLocation(
        RowColumnClass &inRowCol,
        ColorClass &outColor
        ); //Get the RGB values at valid location
    void printImage(); //Print the image to screen
};

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main()
{
    
    cout << "There is nothing here." << endl;
    return (0);
}


#endif

bool ColorClass::clip(int &color)
{
    bool isClip = false; //Tell if it clips

    if (color > FULL)
    {
        color = FULL;
        isClip = true;
    }
    else if (color < EMPTY)
    {
        color = EMPTY;
        isClip = true;
    }

    return(isClip);
}

bool ColorClass::colorChanged(
    int &inRed, 
    int &inGreen, 
    int &inBlue
    )
{
    bool hasChanged = false; //Tell if color has changed
    if (clip(inRed) || clip(inBlue) || clip(inGreen))
    {
        clip(inRed);
        clip(inBlue);
        clip(inGreen);
        hasChanged = true;
    }

    return (hasChanged);
}

ColorClass::ColorClass()
{
    red = FULL;
    green = FULL;
    blue = FULL;
}

ColorClass::ColorClass(
    int inRed,
    int inGreen,
    int inBlue
    )
{
    clip(inRed);
    clip(inGreen);
    clip(inBlue);
    red = inRed;
    green = inGreen;
    blue = inBlue;
}

void ColorClass::setToBlack()
{
    red = EMPTY;
    green = EMPTY;
    blue = EMPTY;
}

void ColorClass::setToRed()
{
    red = FULL;
    green = EMPTY;
    blue = EMPTY;
}

void ColorClass::setToGreen()
{
    red = EMPTY;
    green = FULL;
    blue = EMPTY;
}

void ColorClass::setToBlue()
{
    red = EMPTY;
    green = EMPTY;
    blue = FULL;
}

void ColorClass::setToWhite()
{
    red = FULL;
    green = FULL;
    blue = FULL;
}

bool ColorClass::setTo(
    int inRed,
    int inGreen,
    int inBlue
    )
{
    bool isClip; //Tell if value is out of range

    isClip = colorChanged(inRed, inGreen, inBlue);

    red = inRed;
    green = inGreen;
    blue = inBlue;

    return(isClip);
}

bool ColorClass::setTo(ColorClass &inColor)
{
    bool isClip; //Tell if it's out of range

    isClip = setTo(inColor.red, inColor.green, inColor.blue);

    return (isClip);
}

bool ColorClass::addColor(ColorClass &rhs)
{
    bool isClip; //Tell if it's out of range

    red += rhs.red;
    green += rhs.green;
    blue += rhs.blue;

    isClip = colorChanged(red, green, blue);

    return (isClip);
}

bool ColorClass::subtractColor(ColorClass &rhs)
{
    bool isClip; //Tell if it's out of range

    red -= rhs.red;
    green -= rhs.green;
    blue -= rhs.blue;

    isClip = colorChanged(red, green, blue);

    return (isClip);
}

bool ColorClass::adjustBrightness(double adjFactor)
{
    bool isClip; //Tell if it's out of range

    red = int(red * adjFactor);
    green = int(green * adjFactor);
    blue = int(blue * adjFactor);

    isClip = colorChanged(red, green, blue);

    return (isClip);
}

void ColorClass::printComponentValues()
{
    cout << "R: " << red << " G: " << green << " B: " << blue;
}

RowColumnClass::RowColumnClass()
{
    row = DEFAULT;
    col = DEFAULT;
}

RowColumnClass::RowColumnClass(int inRow, int inCol)
{
    row = inRow;
    col = inCol;
}

void RowColumnClass::setRowCol(int inRow, int inCol)
{
    row = inRow;
    col = inCol;
}

void RowColumnClass::setRow(int inRow)
{
    row = inRow;
}

void RowColumnClass::setCol(int inCol)
{
    col = inCol;
}

int RowColumnClass::getRow()
{
    return (row);
}

int RowColumnClass::getCol()
{
    return (col);
}

void RowColumnClass::addRowColTo(RowColumnClass &inRowCol)
{
    row += inRowCol.row;
    col += inRowCol.col;
}

void RowColumnClass::printRowCol()
{
    cout << "[" << row << "," << col << "]";
}

bool ColorImageClass::isValidLoc(RowColumnClass &inRowCol)
{
    bool valid = false;
    int row, col;
    row = inRowCol.getRow();
    col = inRowCol.getCol();
    if (row < ROW && row >= 0 && col < COL && col >= 0)
    {
        valid = true;
    }

    return (valid);

}

ColorImageClass::ColorImageClass()
{
    int row, col; //Represent the row and col of the image
    for (row = 0; row < ROW; row++)
    {
        for (col = 0; col < COL; col++)
        {
            image[row][col].setToBlack();
        }
    }
}

void ColorImageClass::initializeTo(ColorClass &inColor)
{
    int row, col; //Represent the row and col of the image
    for (row = 0; row < ROW; row++)
    {
        for (col = 0; col < COL; col++)
        {
            image[row][col].setTo(inColor);
        }
    }
}

bool ColorImageClass::addImageTo(ColorImageClass &rhsImg)
{
    int row, col; //Represent the row and col of image
    bool isClip = false; //Tell if the value of color has ever clipped
    for (row = 0; row <ROW; row++)
    {
        for (col = 0; col < COL; col++)
        {
            if (image[row][col].addColor(rhsImg.image[row][col]))
            {
                isClip = true;
            }
        }
    }

    return (isClip);
}

bool ColorImageClass::addImages(
    int numImgsToAdd, 
    ColorImageClass imagesToAdd[]
    )
{
    int i, row, col; //For loop index
    bool isClip = false; //Tell if the value of color has ever clipped

    for (i = 1; i < numImgsToAdd; i++)
    {
        if (imagesToAdd[0].addImageTo(imagesToAdd[i]))
        {
            isClip = true;
        }
    }

    for (row = 0; row < ROW; row++)
    {
        for (col = 0; col < COL; col++)
        {
            image[row][col] = imagesToAdd[0].image[row][col];
        }
    }

    return (isClip);
}

bool ColorImageClass::setColorAtLocation(
    RowColumnClass &inRowCol, 
    ColorClass &inColor
    )
{
    int row, col; //The location for changed value
    bool valid = false; //Tell if the change is valid

    row = inRowCol.getRow();
    col = inRowCol.getCol();
    if (isValidLoc(inRowCol))
    {
        valid = true;
        image[row][col].setTo(inColor);
    }

    return (valid);
}

bool ColorImageClass::getColorAtLocation(
    RowColumnClass &inRowCol,
    ColorClass &outColor
    )
{
    int row, col; //The location to get RGB value
    bool valid = false; //Tell if location is valid

    row = inRowCol.getRow();
    col = inRowCol.getCol();
    if (isValidLoc(inRowCol))
    {
        valid = true;
        outColor.setTo(image[row][col]);
    }

    return (valid);
}

void ColorImageClass::printImage()
{
    int i, j; //For loop index

    for (i = 0; i < ROW; i++)
    {
        image[i][0].printComponentValues();

        for (j = 1; j < COL; j++)
        {
            cout << "--";
            image[i][j].printComponentValues();
        }

        cout << endl;
    }
}