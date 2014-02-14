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
double angle2 (double x1, double y1, double x2, double y2)
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

double dist(double x1,double y1,double x2,double y2)
{
    return sqrt((x1 - x2)*(x1 - x2)+(y1 - y2)*(y1 - y2));
}

int inArc(double x,double y,double x1,double y1,double x2,double y2,double xc,double yc)
{//return (x,y) in Arc ?
    return (dist(x,y,xc,yc) <= dist(x1,y1,xc,yc)) && (angle2(x1-xc,y1-yc,x-xc,y-yc) <= angle2(x1-xc,y1-yc,x2-xc,y2-yc));
}
