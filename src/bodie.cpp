#include "bodie.h"

Bodie::Bodie()
{
}

Circle Bodie::getCircle()
{
    return this->circle;
}

double Bodie::getRadius()
{
    Circle circle = this->getCircle();
    return circle.squared_radius();
}

void Bodie::setCircle(double x, double y, double r, double xf, double yf)
{
    this->circle = Circle(Point(x,y), r);
    this->xf = xf;
    this->yf = yf;
}

void Bodie::print()
{
    Circle circle = this->getCircle();
    Point c = circle.center();
    std::cout << "Bodie:" << std::endl;
    std::cout << "[center: ("<< c.x() << " " << c.y() << "), radius: " << circle.squared_radius() << "]" << std::endl;
}

Bodie::~Bodie()
{
}

std::istream & operator>>(std::istream & istream, Bodie & bodie)
{
    if (istream)
    {
        double xi, yi, r, xf, yf;
        istream >> xi;
        istream >> yi;
        istream >> r;
        istream >> xf;
        istream >> yf;

        bodie.setCircle(xi, yi, r, xf, yf);
    }
    return istream;
}
