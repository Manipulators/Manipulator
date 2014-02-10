#ifndef CRITICALCURVES_H
#define CRITICALCURVES_H

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/create_offset_polygons_2.h>
#include <CGAL/Polygon_2.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K ;
typedef CGAL::Polygon_2<K>           Polygon ;

/* TODO: avoid build error.

Polygon offset (Polygon, double);

*/

#endif
