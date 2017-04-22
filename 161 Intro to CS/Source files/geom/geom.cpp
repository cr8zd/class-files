/******************************************************************************
* Author: Jennifer Frase
* Date Created: 11/24/14
* Last Modification Date: 11/26/14
* Filename: geom.cpp
*
* Overview:
* This program will allow the user to create two points with which to make a
* line segment. The program will then display the line's length and slope.
*
* Input:
* The input will be four numbers corresponding to the x and y coordinates of
* two points.
*
* Output:
* The output for this program can be the length and slope of the line created
* from the two points the user input.
******************************************************************************/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <new>

using namespace std;

//Create a point with an x and y coordinate
class Point
{
    private:
        double xCoor; //x coordinate
        double yCoor; //y coordinate

    public:
        Point(){}; //default constructor

        Point(double xIn, double yIn) //initialize Point with parameters
        { xCoor = xIn, yCoor = yIn;}

        double getX() const //return xCoor
        { return xCoor; }

        double getY() const //return yCoor
        { return yCoor; }

        //Get the difference between xCoor and parameter's xCoor
        double run(const Point &otherP) const
        { return xCoor - otherP.getX(); }

        //Get the difference between yCoor and parameter's yCoor
        double rise(const Point &otherP) const
        { return yCoor - otherP.getY(); }

        //Get return length using Pythagorean equation with respect
        //to the parameter Point
        double distanceTo(const Point &otherP) const
        { return sqrt((rise(otherP) * rise(otherP))
                    + (run(otherP) * run(otherP)));
        }
};

//Create a line from two points
class LineSegment
{
    private:
        Point end1; //End point for the line
        Point end2; //Second end point for the line

    public:
        //initialize LineSegment with parameters
        LineSegment(Point in1, Point in2)
        { end1 = in1, end2 = in2; }

        double length() const //return length
        { return end1.distanceTo(end2); }

        double slope() const //return slope
        { return end1.rise(end2)/ end1.run(end2); }
};

int main()
{
    double xCoor, yCoor; //user input
    char repeat; //user input for making another line

    //Make a line until user doesn't want to make another
    do
    {
        cout << "Making A Line:\n" << endl;
        cout << "What are the coordinates of your first point?" << endl;
        cout << "Please separate your x and y coordinates with whitespace." << endl;
        cin >> xCoor >> yCoor;

        Point point1(xCoor, yCoor); //First user input point

        cout << "\nWhat are the coordinates of your second point?" << endl;
        cout << "Please separate your x and y coordinates with whitespace." << endl;
        cin >> xCoor >> yCoor;

        Point point2(xCoor, yCoor); //Second user input point
        LineSegment line(point1, point2); //Line created from both Points

        //Print Line info
        cout << fixed << showpoint << setprecision(2);
        cout << "\nThe length and slope of the line created by your two points are:" << endl;
        cout << "Length: " << line.length() << endl;
        cout << "Slope: ";
        if(isinf(line.slope()))
            cout << "Vertical." << endl;
        else
            cout << line.slope() << endl;

        //Ask if they want to repeat
        cout << "\nDo you want to do make another line? Y/N" << endl;
        cin >> repeat;
        cout << endl;
    }while (toupper(repeat) == 'Y');

    return 0;
}

