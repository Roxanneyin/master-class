//-------------------member functions for ColorImageClass-------------------//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "ColorImageClass.h"
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "inFileValid.h"
#include "constants.h"

bool ColorImageClass::isValidLoc(RowColumnClass &inRowCol)
{
    bool valid = false;
    int row, col;
    row = inRowCol.getRow();
    col = inRowCol.getCol();
    if (row < imgRow && row >= MIN_PIXEL && col < imgCol && col >= MIN_PIXEL)
    {
        valid = true;
    }

    return (valid);

}

ColorImageClass::ColorImageClass()
{
    image = 0;
    imgRow = DEFAULT_ROW;
    imgCol = DEFAULT_COL;
}

ColorImageClass::ColorImageClass(RowColumnClass &inRowCol)
{
    setImgSize(inRowCol);
}

int ColorImageClass::getRow()
{
    return (imgRow);
}

int ColorImageClass::getCol()
{
    return (imgCol);
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

void ColorImageClass::setImgSize(RowColumnClass &inRowCol)
{
    imgRow = inRowCol.getRow();
    imgCol = inRowCol.getCol();
    delete [] image;
    image = new ColorClass *[imgRow];
    for (int i = 0; i < imgRow; i++)
    {
        image[i] = new ColorClass[imgCol];
    }
}

bool ColorImageClass::readImg(string fileName)
{
    RowColumnClass imgRowCol; //Assign image size to imgRowCol
    RowColumnClass inRowCol; //Temp location when read in color
    ColorClass tempColor; //Temp RGB value when read in color
    string magicNum; //The image type of read in file

    int maxRGB; //maximum value shown in the file
    int row, col;
    ifstream inFile;

    inFile.open(fileName.c_str());
    if (!inFileValid(inFile, false))
    {
        cout << "Unable to open input file" << endl;
        return false;
    }

    inFile >> magicNum;
    if (!inFileValid(inFile, true))
    {
        cout << "Something wrong when read in magic number" << endl;
        return false;
    }

    if (magicNum != MAGIC_NUM)
    {
        cout << "Invalid magic number for ppm file!" << endl;
        return false;
    }

    inFile >> col >> row >> maxRGB;
    if (!inFileValid(inFile, true))
    {
        cout << "Something wrong when read in col/row/maxRGB value" << endl;
        return false;
    }
    if (maxRGB != FULL)
    {
        cout << "Only maximum RGB value 255 is allowed!" << endl;
        return false;
    }
    if (col < MIN_PIXEL || row < MIN_PIXEL ||
    row > MAX_PIXEL || col > MAX_PIXEL)
    {
        cout << "Image size is out of bound!" << endl;
        return false;
    }

    imgRowCol.setRowCol(row, col);
    setImgSize(imgRowCol);

    for (int i = 0; i < imgRow; i++)
    {
        for (int j = 0; j < imgCol; j++)
        {
            if (tempColor.setTo(inFile))
            {
                inRowCol.setRowCol(i, j);
                setColorAtLocation(inRowCol, tempColor);
            }
            else
            {
                cout << "Error: Reading color from file" << endl;
                cout << "Error: Reading image color at row: ";
                cout << i << " " << "col: " << j << endl;
                return false;
            }
        }
    }
    inFile.close();
    return true;
}

bool ColorImageClass::writeImg(string fileName)
{
    ofstream outFile;
    outFile.open(fileName.c_str());
    if(outFile.fail())
    {
        cout << "Unable to open output file" << endl;
        return false;
    }

    outFile << MAGIC_NUM << endl;
    outFile << imgCol << " " << imgRow << endl;
    outFile << FULL << endl;

    for (int i = 0; i < imgRow; i++)
    {
        for (int j = 0; j < imgCol; j++)
        {
            image[i][j].WriteTo(outFile);
        }
        outFile << endl;
    }
    outFile.close();
    return true;
}