/* Program Header - Yuan Yin, 
This is a program to decode and encode ppm files with given message files, 
when user provide valid ppm and message files, this program can hide message
into ppm file. 03-24-2019 */

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include "ColorClass.h"
#include "RowColumnClass.h"
#include "ColorImageClass.h"
#include "StegaClass.h"
#include "isEven.h"
#include "inFileValid.h"
#include "constants.h"

int main(int argc, char *argv[])
{
    if (argc != ARG_NUM)
    {
        cout << "Usage: " << argv[0] << " <startPPM.ppm>" << endl;
        exit(2);
    }

    int choice = DEFAULT_CHOICE; //Users choice to operate this program
    int startRow, startCol; //Start point to encode message file
    string imgFileName; //The file name of original image
    string msgFileName; //The file name of message image
    string outFileName; //The file name of output image
    ColorImageClass image; //The original image class
    StegaClass imgEncode; //The encoded image
    StegaClass imgDecode; //The decoded image

    cout << "Reading initial image from: " << argv[1] << endl;
    imgFileName = argv[1];

    if (image.readImg(imgFileName))
    {
        cout << "Image read successful: Yes" << endl;
    }
    else
    {
        cout << "Image read successful: No" << endl;
        cout << "Error: " 
        << "While reading the image, an error was encountered." << endl;
        cout << "Exiting the program!" << endl;
        exit(3);
    }

    while (choice != EXIT)
    {
        cout << "1. Encode a message from file" << endl;
        cout << "2. Perform decode" << endl;
        cout << "3. Write current image to file" << endl;
        cout << "4. Exit the program" << endl;
        cout << "Enter your choice: ";

        bool validChoice = false;
        while (!validChoice)
        {
            cin >> choice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(IGNORE_NUM, '\n');
                cout << "Please enter a valid int number!" << endl;
                cout << "Enter your choice: ";
            }
            else if ((choice > EXIT) || (choice < ENCODE))
            {
                cout << "Please enter an integer between 1-4!" << endl;
                cout << "Enter your choice: ";
            }
            else
            {
                validChoice = true;
            }
        }
        //Above is to check user input with valid choice

        if (choice == ENCODE)
        {
            cout << "Enter name of file containing message: ";
            cin >> msgFileName;

            cout << "Enter row and column for message placement: ";
            cin >> startRow >> startCol;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(IGNORE_NUM, '\n');
                cout << "Please enter valid row and column number!" << endl;
            }
            else
            {
                if (imgEncode.readMsg(msgFileName))
                {
                    RowColumnClass startRowCol(startRow, startCol);

                    if (imgEncode.encodeImg(startRowCol, image))
                    {
                        cout << "Message encode successful: Yes" << endl;
                    }
                    else
                    {
                        cout << "Message encode successful: No" << endl;
                    }
                }
                else
                {
                    cout << "Message encode successful: No" << endl;
                }
            }
        }
        else if (choice == DECODE)
        {
            if (imgDecode.decodeImg(image))
            {
                cout << "Image modified to decoded image contents" << endl;
            }
            else
            {
                cout << "Image cannot decode successful!" << endl;
            }
        }
        else if (choice == WRITE_IMAGE)
        {
            cout << "Enter name of file to write image to: ";
            cin >> outFileName;

            if (image.writeImg(outFileName))
            {
                cout << "Image write successful: Yes" << endl;
            }
            else
            {
                cout << "Image write successful: No" << endl;
            }
        }
        else if (choice == EXIT)
        {
            cout << "Thanks for using this program!" << endl;
        }
    }
    return (0);
}