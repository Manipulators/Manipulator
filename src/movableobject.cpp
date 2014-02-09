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
    print_polygon(this->getPolygon());
}

MovableObject::~MovableObject()
{
}

std::istream & operator>>(std::istream & istream, MovableObject & movable_object)
{
    if (istream)
    {
        Polygon polygon;
        istream >> polygon;
        movable_object.setPolygon(polygon);
    }
    return istream;
}
