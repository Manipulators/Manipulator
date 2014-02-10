#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "polygon.h"
#include <iostream>


class MovableObject
{
private:
    Polygon polygon;
public:
    // Constructor.
    MovableObject();
    // Get the polygon property of the robot.
    Polygon getPolygon();
    // Set the polygon property of the robot.
    void setPolygon(Polygon);
    // Print a description of the movable object on the standard output.
    void print();
    // Destructor.
    ~MovableObject();
};

// Read the description of the movable object from the given stream.
std::istream & operator>>(std::istream &, MovableObject &);

#endif // MOVABLEOBJECT_H
