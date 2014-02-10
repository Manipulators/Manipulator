#ifndef ROBOT_H
#define ROBOT_H

#include "polygon.h"
#include <iostream>


class Robot
{
private:
    Polygon polygon;
public:
    // Constructor.
    Robot();
    // Get the polygon property of the robot.
    Polygon getPolygon();
    // Set the polygon property of the robot.
    void setPolygon(Polygon);
    // Print a description of the robot on the standard output.
    void print();
    // Destructor.
    ~Robot();
};

// Read the description of the robot from the given stream.
std::istream & operator>>(std::istream &, Robot &);

#endif // ROBOT_H
