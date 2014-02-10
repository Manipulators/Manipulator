#include "polygon.h"


void print_polygon(Polygon polygon)
{
    typename Polygon::Vertex_iterator vertex_iterator;

    std::cout << "[" << polygon.size() << " vertices:";
    for (vertex_iterator = polygon.vertices_begin(); vertex_iterator < polygon.vertices_end(); ++vertex_iterator)
    {
        std::cout << " (" << *vertex_iterator << ")";
    }
    std::cout << "]" << std::endl;

    return;
}

QPolygonF Polygon_CGAL_to_Qt(Polygon polygon)
{
    QPolygonF Pqt;
    typename Polygon::Vertex_iterator vertex_iterator;

    for (vertex_iterator = polygon.vertices_begin(); vertex_iterator < polygon.vertices_end(); ++vertex_iterator)
    {
        double x = CGAL::to_double((*vertex_iterator).x()), y = CGAL::to_double((*vertex_iterator).y());
        Pqt << QPointF(x,y);
    }
    return Pqt;
}
