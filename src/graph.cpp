#include "graph.h"

Graph::Graph()
{
  n = 0;
}

int Graph::index(double xi,double yi)
{
    int i;
    for (i = 0; i < (this->n); i++)
    {
        Node m = (this->nodes)[i];
        if (m.x == xi && m.y == yi) {return i;};
    }
    //Add node
    Node node;
    node.x = xi;
    node.y = yi;
    (this->nodes)[this->n] = node;
    this->n = (this->n) + 1;
    return (this->n) - 1;
}

void Graph::addVertice(double x1,double y1,double x2,double y2,int isarc, double xc =-1,double yc=-1)
{
    int index1 = index(x1,y1);
    int index2 = index(x2,y2);
    Vertice v;
    v.isarc = isarc;
    v.xc = xc;
    v.yc = yc;
    this->matrix[index1][index2] = v;
    this->matrix[index2][index1] = v;
}
