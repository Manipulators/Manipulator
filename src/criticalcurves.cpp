#include <CGAL/enum.h>
#include <math.h>       /* atan2 */
#include "criticalcurves.h"

#define PI 3.14159265




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

//Anticlockwise angle between two vectors.
double angle (double x1, double y1, double x2, double y2 )
{
      double result1, result2;
      result1 = atan2 (y1,x1) * 180 / PI;
      result2 = atan2 (y2,x2) * 180 / PI;
      if (result1 < 0) {result1 = result1 + 360;};
      if (result2 < 0) {result2 = result2 + 360;};
      result1 = result2 - result1;
      if (result1 < 0) {result1 = result1 + 360;};
      return result1;
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
