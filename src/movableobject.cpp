#include "movableobject.h"


MovableObject::MovableObject()
{
}

Circle MovableObject::get()
{
    return this->circle;
}

void MovableObject::set(double x,double y,double r)
{
    this->circle = Circle(Point(x,y),r);
}

void MovableObject::print()
{
    Circle circle = this->get();
    Point c = circle.center();
    std::cout << "MovableObject: center = ("<< c.x() << "," << c.y() << ") raduis= "<< circle.squared_radius() << std::endl;
}

MovableObject::~MovableObject()
{
}

std::istream & operator>>(std::istream & istream, MovableObject & movableobject)
{
    if (istream)
    {
        double x,y,r;
        istream >> x;
        istream >> y;
        istream >> r;

        movableobject.set(x,y,r);
    }
    return istream;
}
