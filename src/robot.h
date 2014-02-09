#ifndef ROBOT_H
#define ROBOT_H

#include "polygon.h"
#include <iostream>


class Robot
{
private:
    Polygon polygon;
public:
    Robot();
    Polygon getPolygon();
    void setPolygon(Polygon);
    ~Robot();
};

std::istream & operator>>(std::istream &, Robot);

#endif // ROBOT_H
