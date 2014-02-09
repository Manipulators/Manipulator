#include "movableobject.h"


MovableObject::MovableObject()
{
}

Polygon MovableObject::getPolygon()
{
    return this->polygon;
}

void MovableObject::setPolygon(Polygon polygon)
{
    this->polygon = polygon;
}

void MovableObject::print()
{
    std::cout << "Movable object:" << std::endl;
    // TODO: complete.
}

MovableObject::~MovableObject()
{
}

std::istream & operator>>(std::istream & istream, MovableObject movable_object)
{
    Polygon polygon;
    if (istream)
    {
        istream >> polygon;
    }
    return istream;
}
