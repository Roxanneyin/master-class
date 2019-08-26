/*This class is to define an object containing information of RGB values,
Each object has red, green, bule values and thus represent a specific color.*/

#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_

#include <iostream>
#include <fstream>
using namespace std;

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

    int getRed();
    int getGreen();
    int getBlue();
    //Three member functions above are to get the value of each RGB color
    
    void setToBlack(); //Set RGB into color black
    void setToRed(); //Set RGB into color red
    void setToGreen(); //Set RGB into color green
    void setToBlue(); //Set RGB into color blue
    void setToWhite(); //Set RGB into color white
    void setToYellow(); //Set RGB into color yellow
    void setToMagenta(); //Set RGB into color magenta
    void setToCyan(); //Set RGB into color cyan

    bool setTo(
        int inRed,
        int inGreen,
        int inBlue
        ); //Set RGB value as input within range
    bool setTo(ColorClass &inColor); //Set all color to same value
    bool setTo(ifstream &inFile); //Set color as the file input
    bool WriteTo(ofstream &outFile); //Write color as the file output

    bool addColor(ColorClass &rhs); //Add RGB value to color object
    bool subtractColor(ColorClass &rhs); //Subtract value to color
    bool adjustBrightness(double adjFactor); //Adjust brightness
    void printComponentValues(); //Print RGB values
};

#endif