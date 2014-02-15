#ifndef GRAPHE_H
#define GRAPHE_H
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Line_2.h>
#include "criticalcurves.h"


// Define the CGAL kernel.
typedef CGAL::Exact_predicates_inexact_constructions_kernel K ;
// Define the CGAL polygon.
typedef CGAL::Polygon_2<K>           Polygon ;
typedef CGAL::Point_2<K>           Point ;
typedef CGAL::Line_2<K>           Line ;
typedef Polygon::Edge_const_iterator EdgeIterator;

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
    //Attention : orientation des arc
    //Original wall or corner (cf. Labeling)
    /*double x1;
    double y1;
    double x2;
    double y2;*/
};

class Graphe
{
public:
    Vertice matrix [100][100];
    Node nodes [100];
    std::list<int> regions [100];
    int n;
    Graphe();
    void addVertice(double,double,double,double,VType, double,double);
    int index(double,double);
    void addOffset(Polygon,double);
    void addOffsets(std::list<Polygon>,double);
    void addOffsetScreen(int,int,double);
    void buildRegion();
};


#endif
