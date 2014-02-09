#include "robot.h"

Robot::Robot()
{
}

Polygon Robot::getPolygon()
{
    return this->polygon;
}

void Robot::setPolygon(Polygon polygon)
{
    this->polygon = polygon;
}

void Robot::print()
{
    std::cout << "Robot:" << std::endl;
    print_polygon(this->getPolygon());
}

Robot::~Robot()
{
}

std::istream & operator>>(std::istream & istream, Robot & robot)
{
    if (istream)
    {
        Polygon polygon;
        istream >> polygon;
        robot.setPolygon(polygon);
    }
    return istream;
}
