#include "obstacles.h"
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>


struct Kernel : public CGAL::Exact_predicates_exact_constructions_kernel {};

typedef CGAL::Polygon_2<Kernel> Polygon_2;

Obstacles::Obstacles()
{
}

Obstacles::~Obstacles()
{
}

std::istream & operator>>(std::istream &is, Obstacles obstacles)
{
    Polygon_2 polygon;
    if (is)
    {
        is >> polygon;
    }
    return is;
}
