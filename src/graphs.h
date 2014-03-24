#ifndef GRAPHS_H
#define GRAPHS_H

#include "criticalcurves.h"
#include "noncriticalregion.h"
#include "roadmap.h"
#include "bodie.h"

#include <lemon/smart_graph.h>
#include <lemon/dijkstra.h>
#include <lemon/list_graph.h>
#include <lemon/graph_to_eps.h>
#include <lemon/math.h>


#include <CGAL/Arr_naive_point_location.h>

#include <CGAL/Arr_landmarks_point_location.h>

typedef CGAL::Arr_naive_point_location<Arrangement_2> Naive_pl;
typedef CGAL::Arr_landmarks_point_location<Arrangement_2> Landmarks_pl;
typedef lemon::SmartDigraph SmartDigraph;
typedef lemon::Dijkstra<SmartDigraph> Dijkstra;

// Condition on adjacent nodes in the manipulation graph
int link(int, int, int, int);

class Graphs
{
public:
    // Constructor
    Graphs();

    void setParameters(double radius_1, double radius_2, Arrangements_2 insets_1, Arrangements_2 insets_2, Arrangements_2 critical_curves, double xri, double yri, double xoi, double yoi, double xrf, double yrf, double xof, double yof);
    // Build non-critical regions graph
    void buildNCRg(double radius_1, double radius_2, Arrangements_2 insets_1, Arrangements_2 insets_2, Arrangements_2 critical_curves, double xri, double yri, double xoi, double yoi, double xrf, double yrf, double xof, double yof);
    // Build manipulation graph
    void buildManipG();
    // Print graph
    void print();

    // 3.4.1
    NonCriticalRegion initial;
    NonCriticalRegion final;
    ACSCell ACSCellinitial;
    ACSCell ACSCellfinal;

    // Search a path in the manipulation graph from ACSCellinitial to ACSCellfinal
    int searchPath();
    // and put the result in path
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

    // Destructor
    ~Graphs();
};

#endif // GRAPHS_H
