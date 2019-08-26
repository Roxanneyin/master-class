/*This class is to define an object containning information of rows and 
columns of an array.*/

#ifndef _ROWCOLUMNCLASS_H_
#define _ROWCOLUMNCLASS_H_

#include <iostream>
using namespace std;

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

#endif