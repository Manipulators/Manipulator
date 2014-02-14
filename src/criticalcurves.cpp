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

double angle1 (double x1, double y1)
{
      double result1;
      result1 = atan2 (y1,x1) * 180 / PI;
      if (result1 < 0) {result1 = result1 + 360;};
      return result1;
}

//Anticlockwise angle between two vectors.
double angle2 (double x1, double y1, double x2, double y2 )
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


void convex(Polygon polygon)
{//polygon.is_counterclockwise_oriented()
    typename Polygon::Vertex_iterator vertex;

    vertex = polygon.vertices_end();
    double xp,yp,x,y,xa,ya;

    xp = CGAL::to_double(vertex->x());
    yp = CGAL::to_double(vertex->y());
    vertex = polygon.vertices_begin();

    for (; vertex < polygon.vertices_end()-1;)
    {
        x = CGAL::to_double(vertex->x());
        y = CGAL::to_double(vertex->y());
        vertex++;
        xa = CGAL::to_double(vertex->x());
        ya = CGAL::to_double(vertex->y());
        if (angle2(x-xp,y-yp,xa-x,ya-y) <= 180) {std::cout << "# (" << x << ","<< y << ") #\n";};
        xp = x;
        yp = y;
        x = xa;
        y = ya;
    };
    vertex = polygon.vertices_begin();
    xa = CGAL::to_double(vertex->x());
    ya = CGAL::to_double(vertex->y());
    if (angle2(x-xp,y-yp,xa-x,ya-y) <= 180) {std::cout << "# (" << x << ","<< y << ") #\n";};
    return;
}
