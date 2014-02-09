#ifndef ROBOT_H
#define ROBOT_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <iostream>


struct Kernel : public CGAL::Exact_predicates_exact_constructions_kernel {};

typedef CGAL::Polygon_2<Kernel> Polygon_2;

class Robot
{
private:
    Polygon_2 polygon;
public:
    Robot();
    Polygon_2 getPolygon();
    void setPolygon(Polygon_2);
    ~Robot();
};

std::istream & operator>>(std::istream &, Robot);

#endif // ROBOT_H
