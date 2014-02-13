#include "graphe.h"

Graphe::Graphe()
{
}

int Graphe::index(double xi,double yi)
{
    int i;
    for (i = 0; i < (this->n); i++)
    {
        std::cout << "i = " << i << std::endl;
        std::cout << "this->n = " << this->n << std::endl;
        std::cout << "Test point 1" << std::endl;
        Node m = (this->nodes)[i];
        std::cout << "Test point 2" << std::endl;
        if (m.x == xi && m.y == yi) {return i;};
        std::cout << "Test point 3" << std::endl;
        // J'ai un i random au segmentation fault, un this->n abusif et perdu du temps avec une connerie...
    }
    //Add node
    Node node;
    node.x = xi;
    node.y = yi;
    (this->nodes)[this->n] = node;
    this->n = (this->n) + 1;
    return (this->n) - 1;
}

void Graphe::addVertice(double x1,double y1,double x2,double y2,VType vtype, double xc =-1,double yc=-1)
{
    int index1 = index(x1,y1);
    int index2 = index(x2,y2);
    Vertice v;
    v.vtype = vtype;
    v.xc = xc;
    v.yc = yc;
    this->matrix[index1][index2] = v;
    this->matrix[index2][index1] = v;
    return ;
}

void Graphe::addOffset(Polygon polygon)
{
    typename Polygon::Vertex_iterator vertex;

    vertex = polygon.vertices_begin();
    double xp,yp,x,y;

    xp = CGAL::to_double(vertex->x());
    yp = CGAL::to_double(vertex->y());
    vertex++;

    for (; vertex < polygon.vertices_end(); ++vertex)
    {
        x = CGAL::to_double(vertex->x());
        y = CGAL::to_double(vertex->y());

        this->addVertice(xp,yp,x,y,Seg);
        xp = x;
        yp = y;
    };
    vertex = polygon.vertices_begin();
    x = CGAL::to_double(vertex->x());
    y = CGAL::to_double(vertex->y());
    this->addVertice(xp,yp,x,y,Seg);

    return;
}

void Graphe::addOffsets(std::list<Polygon> polygons)
{
    std::list<Polygon>::iterator polygon;
    for (polygon = polygons.begin(); polygon != polygons.end(); ++polygon)
    {
        this->addOffset(* polygon);
    };
    return;
}

void Graphe::addOffsetScreen(int w,int h,double r)
{
    this->addVertice(r,r,w-r,r,Seg);
    this->addVertice(w-r,r,w-r,h-r,Seg);
    this->addVertice(w-r,h-r,r,h-r,Seg);
    this->addVertice(r,h-r,r,r,Seg);
    return;
}
