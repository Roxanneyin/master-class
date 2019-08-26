//--------------------member functions for RowColumnClass--------------------//

#include <iostream>
using namespace std;

#include "RowColumnClass.h"
#include "constants.h"

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