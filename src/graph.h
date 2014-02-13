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
    int isarc;
    double xc;
    double yc;
    //Original wall or corner (cf. Labeling)
    /*double x1;
    double y1;
    double x2;
    double y2;*/
};

class Graph
{
private:
    Vertice matrix [1000][1000];
    Node nodes [1000];
public:
    int n;
    Graph();
    void addVertice(double,double,double,double,int, double,double);
    int index(double,double);
};


#endif
