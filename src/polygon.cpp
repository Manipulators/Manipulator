#include "polygon.h"


void print_polygon(Polygon_2 polygon)
{
    typename Polygon_2::Vertex_iterator vertex;

    std::cout << "[" << polygon.size() << " vertices:";
    for (vertex = polygon.vertices_begin(); vertex < polygon.vertices_end(); ++vertex)
    {
        std::cout << " (" << * vertex << ")";
    }
    std::cout << "]" << std::endl;

    return;
}

QPolygonF Polygon_CGAL_to_Qt(Polygon_2 polygon)
{
    QPolygonF polygon_f;
    typename Polygon_2::Vertex_iterator vertex;

    for (vertex = polygon.vertices_begin(); vertex < polygon.vertices_end(); ++vertex)
    {
        double x = CGAL::to_double(vertex->x());
        double y = CGAL::to_double(vertex->y());
        polygon_f << QPointF(x, y);
    }
    return polygon_f;
}
