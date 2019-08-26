//--------------------member functions for StegaClass--------------------//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "StegaClass.h"
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "ColorImageClass.h"
#include "inFileValid.h"
#include "isEven.h"
#include "constants.h"

StegaClass::StegaClass()
{
    message = 0;
    msgRow = DEFAULT_ROW;
    msgCol = DEFAULT_COL;
}

void StegaClass::setSizeTo(RowColumnClass &inRowCol)
{
    msgRow = inRowCol.getRow();
    msgCol = inRowCol.getCol();
    delete [] message;
    message = new int *[msgRow];
    for (int i = 0; i < msgRow; i++)
    {
        message[i] = new int [msgCol];
    }
}

bool StegaClass::readMsg(string fileName)
{
    RowColumnClass msgRowCol;
    ifstream inFile;
    inFile.open(fileName.c_str());
    if (!inFileValid(inFile, false))
    {
        cout << "Unable to open message file." << endl;
        return false;
    }

    inFile >> msgCol >> msgRow;
    if (!inFileValid(inFile, true))
    {
        cout << "Something wrong with col/row of message file" << endl;
        return false;
    }
    if (msgCol < MIN_PIXEL || msgRow < MIN_PIXEL)
    {
        cout << "Invalid message file size!" << endl;
        return false;
    }

    msgRowCol.setRowCol(msgRow, msgCol);
    setSizeTo(msgRowCol);
    for (int i = 0; i < msgRow; i++)
    {
        for (int j = 0; j < msgCol; j++)
        {
            inFile >> message[i][j];
            if (!inFileValid(inFile, true))
            {
                cout << "Error: Reading message value at row/col: ";
                cout << i << " " << j << endl;
                return false;
            }
        }
    }
    return true;
}

void StegaClass::setToEven(int &num)
{
    if (!isEven(num))
    {
        num -= 1;
    }
}

void StegaClass::setToOdd(int &num)
{
    if (isEven(num))
    {
        num += 1;
    }
}

bool StegaClass::encodeColor(int msgVal, ColorClass &inColor)
{
    int inRed = inColor.getRed();
    int inGreen = inColor.getGreen();
    int inBlue = inColor.getBlue();

    if (msgVal == BLACK)
    {
        setToEven(inRed);
        setToEven(inGreen);
        setToEven(inBlue);
    }
    else if (msgVal == RED)
    {
        setToOdd(inRed);
        setToEven(inGreen);
        setToEven(inBlue);
    }
    else if (msgVal == GREEN)
    {
        setToEven(inRed);
        setToOdd(inGreen);
        setToEven(inBlue);
    }
    else if (msgVal == BLUE)
    {
        setToEven(inRed);
        setToEven(inGreen);
        setToOdd(inBlue);
    }
    else if (msgVal == WHITE)
    {
        setToOdd(inRed);
        setToOdd(inGreen);
        setToOdd(inBlue);
    }
    else if (msgVal == YELLOW)
    {
        setToOdd(inRed);
        setToOdd(inGreen);
        setToEven(inBlue);
    }
    else if (msgVal == MAGENTA)
    {
        setToOdd(inRed);
        setToEven(inGreen);
        setToOdd(inBlue);
    }
    else if (msgVal == CYAN)
    {
        setToEven(inRed);
        setToOdd(inGreen);
        setToOdd(inBlue);
    }
    else
    {
        cout << "Invalid message encoded color value!" << endl;
        return false;
    }
    inColor.setTo(inRed, inGreen, inBlue);
    return true;
}

bool StegaClass::decodeColor(ColorClass &inColor)
{
    int inRed = inColor.getRed();
    int inGreen = inColor.getGreen();
    int inBlue = inColor.getBlue();
    if (isEven(inRed))
    {
        if (isEven(inGreen))
        {
            if (isEven(inBlue))
            {
                inColor.setToBlack();
            }
            else
            {
                inColor.setToBlue();
            }
        }
        else
        {
            if (isEven(inBlue))
            {
                inColor.setToGreen();
            }
            else
            {
                inColor.setToCyan();
            }
        }
    }
    else
    {
        if (isEven(inGreen))
        {
            if (isEven(inBlue))
            {
                inColor.setToRed();
            }
            else
            {
                inColor.setToMagenta();
            }
        }
        else
        {
            if (isEven(inBlue))
            {
                inColor.setToYellow();
            }
            else
            {
                inColor.setToWhite();
            }
        }
    }
    return true;
}

bool StegaClass::encodeImg(RowColumnClass &startRowCol, ColorImageClass &inImg)
{
    ColorClass tempColor;
    RowColumnClass inRowCol;
    int imgRow = inImg.getRow(), imgCol = inImg.getCol();
    int startRow = startRowCol.getRow(), startCol = startRowCol.getCol();
    int encodeRow, encodeCol;

    if ((imgRow - 1 < startRow) || (imgCol - 1 < startCol))
    {
        return true;
    }

    if (msgRow < imgRow - startRow)
    {
        encodeRow = msgRow;
    }
    else
    {
        encodeRow = imgRow - startRow;
    }

    if (msgCol < imgCol - startCol)
    {
        encodeCol = msgCol;
    }
    else
    {
        encodeCol = imgCol - startCol;
    }

    for (int i = 0; i < encodeRow; i++)
    {
        for (int j = 0; j < encodeCol; j++)
        {
            inRowCol.setRowCol(startRow + i, startCol + j);
            inImg.getColorAtLocation(inRowCol, tempColor);

            if (encodeColor(message[i][j], tempColor))
            {
                inImg.setColorAtLocation(inRowCol, tempColor);
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

bool StegaClass::decodeImg(ColorImageClass &inImg)
{
    ColorClass tempColor;
    RowColumnClass inRowCol;

    for (int i = 0; i < inImg.getRow(); i++)
    {
        for (int j = 0; j < inImg.getCol(); j++)
        {
            inRowCol.setRowCol(i, j);
            inImg.getColorAtLocation(inRowCol, tempColor);

            if (decodeColor(tempColor))
            {
                inImg.setColorAtLocation(inRowCol, tempColor);
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}