//--------------------member functions for ColorClass--------------------//

#include <iostream>
#include <fstream>
using namespace std;

#include "ColorClass.h"
#include "inFileValid.h"
#include "constants.h"

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

int ColorClass::getRed()
{
    return (red);
}

int ColorClass::getGreen()
{
    return (green);
}

int ColorClass::getBlue()
{
    return (blue);
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

void ColorClass::setToYellow()
{
    red = FULL;
    green = FULL;
    blue = EMPTY;
}

void ColorClass::setToMagenta()
{
    red = FULL;
    green = EMPTY;
    blue = FULL;
}

void ColorClass::setToCyan()
{
    red = EMPTY;
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

bool ColorClass::setTo(ifstream &inFile)
{
    int inRed, inGreen, inBlue;

    inFile >> inRed >> inGreen >> inBlue;

    if (!inFileValid(inFile, true))
    {
        return false;
    }

    red = inRed;
    green = inGreen;
    blue = inBlue;

    if (colorChanged(red, green, blue))
    {
        return false;
    }

    return true;
}

bool ColorClass::WriteTo(ofstream &outFile)
{
    outFile << red << " " << green << " " << blue << " ";
    return true;
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