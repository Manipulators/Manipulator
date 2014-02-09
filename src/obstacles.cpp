#include "obstacles.h"


Obstacles::Obstacles()
{
}

std::list<Polygon> Obstacles::getPolygons()
{
    return this->polygons;
}

void Obstacles::setPolygons(std::list<Polygon> polygons)
{
    this->polygons = polygons;
}

Obstacles::~Obstacles()
{
}

std::istream & operator>>(std::istream & istream, Obstacles obstacles)
{
    std::list<Polygon> polygons;
    while (istream)
    {
        Polygon polygon;
        istream >> polygon;
        polygons.push_back(polygon);
    }
    obstacles.setPolygons(polygons);

    return istream;
}
