#ifndef POLYGON_H
#define POLYGON_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <QGraphicsScene>
#include <QPointF>


// Define the CGAL kernel.
typedef CGAL::Exact_predicates_inexact_constructions_kernel K ;
// Define the CGAL polygon.
typedef CGAL::Polygon_2<K>           Polygon ;




// Print a description of the CGAL polygon on the standard output.
void print_polygon(Polygon);
// Convert CGAL polygon to Qt polygon.
QPolygonF Polygon_CGAL_to_Qt(Polygon);

#endif // POLYGON_H
