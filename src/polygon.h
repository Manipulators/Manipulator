#ifndef POLYGON_H
#define POLYGON_H

#include <CGAL/Cartesian.h>
#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Polygon_2.h>
#include <QGraphicsScene>
#include <QPointF>


// Define the CGAL rational kernel.
typedef CGAL::CORE_algebraic_number_traits Nt_traits;
typedef Nt_traits::Rational Rational;
struct Rat_kernel : public CGAL::Cartesian<Rational> {};


// Define the CGAL polygon.
typedef CGAL::Polygon_2<Rat_kernel> Polygon_2;




// Print a description of the CGAL polygon on the standard output.
void print_polygon(Polygon_2);
// Convert CGAL polygon to Qt polygon.
QPolygonF Polygon_CGAL_to_Qt(Polygon_2);

#endif // POLYGON_H
