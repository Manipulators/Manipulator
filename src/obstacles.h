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
    Obstacles();
    std::list<Polygon> getPolygons();
    void setPolygons(std::list<Polygon> polygons);
    ~Obstacles();
};

std::istream & operator>>(std::istream &, Obstacles);

#endif // OBSTACLES_H
