#ifndef GRAPH_H
#define GRAPH_H

#include <list>

struct Node
{
    double x;
    double y;
};

struct Vertice
{
    Node node;
    int isarc;
    double xc;
    double yc;
};

class Graph
{
private:
    std::list<Vertice> graphe [1000];
public:
    int n;
    Graph();
};


#endif
