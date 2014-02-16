#ifndef CRITICALCURVES_H
#define CRITICALCURVES_H

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/create_offset_polygons_2.h>
#include <CGAL/Polygon_2.h>


// Define the CGAL kernel.
typedef CGAL::Exact_predicates_inexact_constructions_kernel K ;
// Define the CGAL polygon.
typedef CGAL::Polygon_2<K>           Polygon ;
typedef K::Point_2           Point;
typedef CGAL::Line_2<K>           Line ;


Polygon offset (Polygon, double);
std::list<Polygon> offsets(std::list<Polygon>, double);
double angle1 (double, double);
double angle2 (double, double, double, double);

#endif
