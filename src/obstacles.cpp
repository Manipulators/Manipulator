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

void Obstacles::print()
{
    std::list<Polygon> polygons = this->getPolygons();
    std::list<Polygon>::iterator iterator;
    std::cout << "Obstacles:" << std::endl;
    for (iterator = polygons.begin(); iterator != polygons.end(); ++iterator)
    {
        print_polygon(* iterator);
    }
}

Obstacles::~Obstacles()
{
}

std::istream & operator>>(std::istream & istream, Obstacles & obstacles)
{
    std::list<Polygon> polygons;
    while (istream)
    {
        Polygon polygon;
        istream >> polygon;
        if (polygon.size() != 0)
        {
            polygons.push_back(polygon);
        }
    }
    obstacles.setPolygons(polygons);

    return istream;
}
