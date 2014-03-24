#ifndef GRAPHS_H
#define GRAPHS_H

#include "criticalcurves.h"
#include "noncriticalregion.h"
#include <lemon/smart_graph.h>
#include <lemon/dijkstra.h>

#include <lemon/list_graph.h>
#include <lemon/graph_to_eps.h>
#include <lemon/math.h>

typedef lemon::SmartDigraph SmartDigraph;
typedef lemon::Dijkstra<SmartDigraph> Dijkstra;

int link(int, int, int, int);

class Graphs
{
public:
    Graphs();
    void setParameters(double radius_1, double radius_2, Arrangements_2 insets_1, Arrangements_2 insets_2, Arrangements_2 critical_curves);
    // Build non-critical regions graph
    void buildNCRg(double radius_1, double radius_2, Arrangements_2 insets_1, Arrangements_2 insets_2, Arrangements_2 critical_curves);
    // Build manipulation graph
    void buildManipG();
    // 3.4.2
    void print();

    int searchPath(ACSCell, ACSCell);
    std::list<GraspCell> path;
    // Non-critical regions associated graph
    SmartDigraph NCRg;
    // Non-critical regions associated to a node
    std::map< SmartDigraph::Node,NonCriticalRegion> noncriticalregion;

    // Manipulation Graph
    SmartDigraph ManipG;
    // is it a transit arc
    std::map< SmartDigraph::Arc,int> istransit;
    // Graspcell associated to a node
    std::map< SmartDigraph::Node,GraspCell> graspcell_map;

    void exportEPS();

    ~Graphs();
};

#endif // GRAPHS_H
