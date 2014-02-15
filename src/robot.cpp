#include "robot.h"

Robot::Robot()
{
}

Circle Robot::get()
{
    return this->circle;
}

double Robot::r()
{
    Circle circle = this->get();
    return circle.squared_radius();
}

void Robot::set(double x,double y,double r,double xf,double yf)
{
    this->circle = Circle(Point(x,y),r);
    this->xf = xf;
    this->yf = yf;
}

void Robot::print()
{
    Circle circle = this->get();
    Point c = circle.center();
    std::cout << "Robot: center = ("<< c.x() << "," << c.y() << ") raduis = "<< circle.squared_radius() << std::endl;
}

Robot::~Robot()
{
}

std::istream & operator>>(std::istream & istream, Robot & robot)
{
    if (istream)
    {
        double x,y,r,xf,yf;
        istream >> x;
        istream >> y;
        istream >> r;
        istream >> xf;
        istream >> yf;

        robot.set(x,y,r,xf,yf);
    }
    return istream;
}
