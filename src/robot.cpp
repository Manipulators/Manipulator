#include "robot.h"

Robot::Robot()
{
}

Circle Robot::get()
{
    return this->circle;
}

void Robot::set(double x,double y,double r)
{
    this->circle = Circle(Point(x,y),r);
}

void Robot::print()
{
    Circle circle = this->get();
    Point c = circle.center();
    std::cout << "Robot: center = ("<< c.x() << "," << c.y() << ") raduis= "<< circle.squared_radius() << std::endl;
}

Robot::~Robot()
{
}

std::istream & operator>>(std::istream & istream, Robot & robot)
{
    if (istream)
    {
        double x,y,r;
        istream >> x;
        istream >> y;
        istream >> r;

        robot.set(x,y,r);
    }
    return istream;
}
