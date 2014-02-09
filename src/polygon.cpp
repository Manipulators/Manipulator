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
