#include "criticalcurves.h"



Polygon offset (Polygon poly, double lOffset)
{
    return **(CGAL::create_offset_polygons_2<Polygon>(-lOffset,*(CGAL::create_interior_straight_skeleton_2(poly)))).begin();
}

std::list<Polygon> offsets(std::list<Polygon> polygons, double lOffset)
{
    std::list<Polygon>::iterator polygon;
    std::list<Polygon> l;

    for (polygon = polygons.begin(); polygon != polygons.end(); ++polygon)
    {
        l.push_back( offset( (*polygon),lOffset) );
    }
    return l;
}
