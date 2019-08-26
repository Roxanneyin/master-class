#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <iostream>
#include <string>
using namespace std;

const int FULL = 255; //The full(maximum) value of a color
const int EMPTY = 0; //The minimum value of a color

const int ENCODE = 1;
const int DECODE = 2;
const int WRITE_IMAGE = 3;
const int EXIT = 4;
const int DEFAULT_CHOICE = 0;
//Users choices and initialization of the chioce

const int IGNORE_NUM = 200; //Used when error checking of cin operation
const int ARG_NUM = 2; //Number of arguments input of main function
const int MAX_PIXEL = 2000; //The upper bound of dynamic allocation dimension
const int MIN_PIXEL = 0;

const string MAGIC_NUM = "P3"; //Magic number for ppm files
const int DEFAULT = -99999; //Initialization to col and row
const int DEFAULT_ROW = 0, DEFAULT_COL = 0; //Initialization of class object

const int BLACK = 0, RED = 1, GREEN = 2, BLUE = 3;
const int WHITE = 4, YELLOW = 5, MAGENTA = 6, CYAN = 7;
//Eight colors in message file

#endif