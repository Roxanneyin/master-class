#include <iostream>
using namespace std;

/* Program Header - Yuan Yin, 
This is a program to compute area between cubic function and X-axis 
or give exact number of rectangles needed to approximate the area
to reach user given precision, 01-27-2019 */

const int RECT_LIM = 100; /* This the upper bound of rectangles to be tried 
to approximate the area */
const int APPRO_AREA = 1; /* This represents the first choice of the menu, 
to approximate the area with user define parameters. */
const int RECT_NEED = 2; /* This represents the second choice of the menu,
to approximate the number of rectangles needed 
to achieve the precision user defined */
const int EXIT = 3; /* This represents the third chioce of the menu, 
exit the program */

//Function: printMenu - Print out the choices for users to choose
void printMenu();

/* Function: toThePower - Raise the "val" to the power "power" 
and return the result */
double toThePower(double val, int power);

/* Function: evaluateCubicFormula - Test the result value of cubic formula 
and return true if value is non-negative, return false if it's negative */
bool evaluateCubicFormula(
    double aCoeff, 
    double bCoeff, 
    double cCoeff, 
    double dCoeff, 
    double xValue, 
    double &resultVal
    );

/* Function: approximateAreaWithRect - Compute the area between cubic function 
and X-axis */
double approximateAreaWithRect(
    double aCoeff, 
    double bCoeff, 
    double cCoeff, 
    double dCoeff, 
    double startX, 
    double endX, 
    int numRects
    );

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main()
{
    int choice = 0; //The choice according to the menu by users, initialize 
    //with 0
    int numRects; //Number of rectangles used to approximate area
    double aCoeff; //Coefficient for x^3 term in cubic function
    double bCoeff; //Coefficient for x^2 term in cubic function
    double cCoeff; //Coefficient for x term in cubic function
    double dCoeff; //Coefficient for constant term in cubic function
    double startX; //Start point of the interval to be computed
    double endX; //End point of the interval to be computed
    double area; //Area of the sum of rectangles
    double corrAns; //Correct answer of the area between cubic function and 
    //X-axis
    double precision; //Precision that users want to acchive to approximate area
    double errorArea; //Error between correct answer and answer computed by 
    //program
    bool acchivePre = false; /* To test if using no more than 100 rectangles 
    can reach to the user defined precision, initialized with false */
   
    while(choice != EXIT)
    {
        
        printMenu();
        
        cout << "YOUR CHOICE: ";
        cin >> choice;
        
        if (choice == APPRO_AREA || choice == RECT_NEED)
        //If user chooce 1 or 2 on the menu
        {
            cout << 
            "Enter (a b c d) for function y = a*x^3 + b*x^2 + c*x + d: ";
            cin >> aCoeff >> bCoeff >> cCoeff >> dCoeff;
            
            cout << "Now enter x start and end values: ";
            cin >> startX >> endX;
            
            if (choice == APPRO_AREA) //If user choose 1 on the menu
            {
                cout << "Enter the number of rectangles to use: ";
                cin >> numRects;
                
                area = approximateAreaWithRect(
                    aCoeff, 
                    bCoeff, 
                    cCoeff, 
                    dCoeff, 
                    startX, 
                    endX, 
                    numRects
                    );
                
                cout << "Rectangle result is: " << area << endl;
            }
            else //If user choose 2 on the menu
            {
                cout << "Enter correct answer: ";
                cin >> corrAns;
                
                cout << "Enter precision to reach: ";
                cin >> precision;

                numRects = 1; // Initialize numRects with 1 and to be added to 
                //100

                do{
                    area = approximateAreaWithRect(
                        aCoeff,
                        bCoeff,
                        cCoeff,
                        dCoeff,
                        startX,
                        endX,
                        numRects
                        );
                    errorArea = area - corrAns;

                    numRects++;
                }
                while(numRects <= RECT_LIM && 
                    (errorArea > precision || errorArea < -precision)); 
                /* When number of rectangles loop 100 times, compute and check 
                if the error is smaller than the precision user given.
                If it reaches the precision within 100 rectangles, 
                the loop will stop */

                if (numRects <= RECT_LIM && 
                    errorArea <= precision && errorArea >= - precision)
                {
                    cout << 
                    "Rectangles needed to reach precision: " 
                    << --numRects 
                    << endl;
                }
                else
                {
                    cout << 
                    "Tried 100 rectangles without reaching precision" 
                    << endl;
                }
                /* Check if number of rectangles has gone up to 100,
                and if the error has reached to the precision user given */
            }
        }
        else //If user choose 3 on the menu
        {
            cout << "Thanks for using this program" << endl;
        }
    }

    return (0);
}

#endif

void printMenu()
{
    cout << "1 Approximate Integral Using Rectangles"  << endl;
    cout << "2 Experiment With Rectangle Precision" << endl;
    cout << "3 Quit The Program" << endl;

    return;
}

double toThePower(double val, int power)
{
    int i; //For loop index
    double powerVal = 1.0; //The result of the power of value, initialized with 
    //1
    
    for (i = 1; i <= power; i++)
    {
        powerVal = powerVal * val;
    }

    return (powerVal);
}

bool evaluateCubicFormula(
    double aCoeff, 
    double bCoeff, 
    double cCoeff, 
    double dCoeff, 
    double xValue, 
    double &resultVal
    )
{
    resultVal = 
    aCoeff * toThePower(xValue, 3) 
    + bCoeff * toThePower(xValue, 2) 
    + cCoeff * xValue 
    + dCoeff; //Compute the value of cubic function at point xValue

    if (resultVal < 0)
    {
        return (false);
    }
    else
    {
        return (true);
    }
}

double approximateAreaWithRect(
    double aCoeff, 
    double bCoeff, 
    double cCoeff, 
    double dCoeff, 
    double startX, 
    double endX, 
    int numRects
    )
{
    int i; //For loop index
    double width; //This is the width of each rectangle
    double midPoint; //This is the midpoint of rectangle
    double area = 0; /* This is the approximate area 
    between cubic function and X-axis, initialized with 0 */
    double midVal; //This is the value of cubic function at midpoints
    bool signOfVal; /* Test sign of value at specific point of cubic function, 
    true if it's non-negative, false if it's negative*/
    
    width = (endX - startX) / numRects;
    
    for (i = 0; i < numRects; i++)
    {
        midPoint = startX + width / 2 + width * i;
        signOfVal = evaluateCubicFormula(
            aCoeff, 
            bCoeff, 
            cCoeff, 
            dCoeff, 
            midPoint, 
            midVal
            );
        
        if (signOfVal)
        {
            area += midVal * width;
        }
        else
        {
            area -= midVal * width;
        }
    }

    return (area);
}