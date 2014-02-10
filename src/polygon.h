#ifndef POLYGON_H
#define POLYGON_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <QGraphicsScene>
#include <QPointF>


// Define the CGAL kernel.
struct Kernel : public CGAL::Exact_predicates_exact_constructions_kernel {};
// Define the CGAL polygon.
typedef CGAL::Polygon_2<Kernel> Polygon;

// Print a description of the CGAL polygon on the standard output.
void print_polygon(Polygon);
// Convert CGAL polygon to Qt polygon.
QPolygonF Polygon_CGAL_to_Qt(Polygon);

#endif // POLYGON_H
