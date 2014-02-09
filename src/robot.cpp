#include "robot.h"

Robot::Robot()
{
}

Polygon_2 Robot::getPolygon()
{
    return this->polygon;
}

void Robot::setPolygon(Polygon_2 polygon)
{
    this->polygon = polygon;
}

Robot::~Robot()
{
}

std::istream & operator>>(std::istream &is, Robot robot)
{
    if (is)
    {
        Polygon_2 polygon;
        is >> polygon;
        robot.setPolygon(polygon);
    }
    return is;
}
