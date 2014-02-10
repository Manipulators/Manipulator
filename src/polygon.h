#ifndef POLYGON_H
#define POLYGON_H

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <QGraphicsScene>
#include <QPointF>


struct Kernel : public CGAL::Exact_predicates_exact_constructions_kernel {};

typedef CGAL::Polygon_2<Kernel> Polygon;

void print_polygon(Polygon);

QPolygonF Polygon_CGAL_to_Qt(Polygon);

#endif // POLYGON_H
