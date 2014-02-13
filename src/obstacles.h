#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "polygon.h"
#include <iostream>
#include <list>


class Obstacles
{
private:
    std::list<Polygon> polygons;
public:
    // Constructor.
    Obstacles();
    // Get the polygons property of the obstacles.
    std::list<Polygon> getPolygons();
    // Set the polygons property of the obstacles.
    void setPolygons(std::list<Polygon> polygons);
    // Print a description of the obstacles on the standard output.
    void print();
    // Destructor.
    ~Obstacles();
};

// Read the description of the obstacles from the given stream.
std::istream & operator>>(std::istream &, Obstacles &);

#endif // OBSTACLES_H
