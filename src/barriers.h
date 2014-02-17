#ifndef BARRIERS_H
#define BARRIERS_H

#include "polygon.h"
#include <iostream>


class Barriers
{
private:
    Polygon polygon;
public:
    // Constructor.
    Barriers();
    // Get the polygon property of the barriers.
    Polygon getPolygon();
    // Set the polygon property of the barriers.
    void setPolygon(Polygon polygon);
    // Print a description of the barriers on the standard output.
    void print();
    // Destructor.
    ~Barriers();
};

// Read the description of the barriers from the given stream.
std::istream & operator>>(std::istream &, Barriers &);

#endif // BARRIERS_H
