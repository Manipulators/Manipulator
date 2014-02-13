#ifndef GRAPH_H
#define GRAPH_H
#include <list>

struct Node
{
    double x;
    double y;
};

enum VType {None,Seg,Arc};

struct Vertice
{
    VType vtype;
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
public:
    Vertice matrix [1000][1000];
    Node nodes [1000];
    int n;
    Graph();
    void addVertice(double,double,double,double,VType, double,double);
    int index(double,double);
};


#endif
