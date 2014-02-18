#include "barriers.h"

Barriers::Barriers()
{
}

Polygon Barriers::getPolygon()
{
    return this->polygon;
}

void Barriers::setPolygon(Polygon polygon)
{
    this->polygon = polygon;
}

void Barriers::print()
{
    std::cout << "Barriers" << std::endl;
    print_polygon(this->getPolygon());
}

Barriers::~Barriers()
{
}

std::istream & operator>>(std::istream & istream, Barriers & barriers)
{
    Polygon polygon;
    istream >> polygon;
    barriers.setPolygon(polygon);

    return istream;
}
