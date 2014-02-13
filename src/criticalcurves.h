#ifndef CRITICALCURVES_H
#define CRITICALCURVES_H

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/create_offset_polygons_2.h>
#include <CGAL/Polygon_2.h>


// Define the CGAL kernel.
typedef CGAL::Exact_predicates_inexact_constructions_kernel K ;
// Define the CGAL polygon.
typedef CGAL::Polygon_2<K>           Polygon ;


Polygon offset (Polygon, double);
std::list<Polygon> offsets(std::list<Polygon>, double);

#endif
