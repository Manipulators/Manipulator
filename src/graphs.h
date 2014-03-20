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


class Graphs
{
public:
    Graphs();
    void setParameters(double radius_1, double radius_2, Arrangements_2 insets_1, Arrangements_2 insets_2, Arrangements_2 critical_curves);
    void buildNCRg(double radius_1, double radius_2, Arrangements_2 insets_1, Arrangements_2 insets_2, Arrangements_2 critical_curves);
    void buildManipG();
    // Non-critical regions associated graph
    SmartDigraph NCRg;
    // Non-critical regions associated to a node
    std::map< SmartDigraph::Node,NonCriticalRegion> noncriticalregion;

    // Manipulation Graph
    SmartDigraph ManipG;
    // Non-critical regions associated to a node
    std::map< SmartDigraph::Arc,int> istransit;

    void exportEPS();

    ~Graphs();
};

#endif // GRAPHS_H
