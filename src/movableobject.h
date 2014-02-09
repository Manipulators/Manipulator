#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "polygon.h"
#include <iostream>


class MovableObject
{
private:
    Polygon polygon;
public:
    MovableObject();
    Polygon getPolygon();
    void setPolygon(Polygon);
    ~MovableObject();
};

std::istream & operator>>(std::istream &, MovableObject);

#endif // MOVABLEOBJECT_H
