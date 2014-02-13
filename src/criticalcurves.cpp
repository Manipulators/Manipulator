#include <CGAL/enum.h>
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


/*void convex(Polygon polygon)
{
    typename Polygon::Vertex_iterator vertex;
    typename Polygon::Vertex_iterator vertex1;
    typename Polygon::Vertex_iterator vertex2;
    typename Polygon::Vertex_iterator vertex3;

    vertex = polygon.vertices_begin();
    vertex1 = vertex;
    ++vertex;
    vertex2 = vertex;
    ++vertex;

    for (; vertex < polygon.vertices_end(); ++vertex)
    {
        vertex3 = vertex;
        std::cout << " #" << *vertex2 << "#";
        vertex1 = vertex2;
        vertex2 = vertex3;
    };

    return;
}*/
