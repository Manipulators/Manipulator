#ifndef GRAPHE_H
#define GRAPHE_H

// Constructing an arrangement of various conic arcs.
#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Arr_conic_traits_2.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Arr_naive_point_location.h>

typedef CGAL::CORE_algebraic_number_traits              Nt_traits;
typedef Nt_traits::Rational                             Rational;
typedef Nt_traits::Algebraic                            Algebraic;
typedef CGAL::Cartesian<Rational>                       Rat_kernel;
typedef Rat_kernel::Point_2                             Rat_point_2;
typedef Rat_kernel::Segment_2                           Rat_segment_2;
typedef Rat_kernel::Circle_2                            Rat_circle_2;
typedef CGAL::Cartesian<Algebraic>                      Alg_kernel;
typedef CGAL::Arr_conic_traits_2<Rat_kernel, Alg_kernel, Nt_traits> Traits_2;
typedef Traits_2::Point_2                               Point_2;
typedef Traits_2::Curve_2                               Conic_arc_2;
typedef CGAL::Arrangement_2<Traits_2>                   Arrangement_2;
typedef CGAL::Arr_naive_point_location<Arrangement_2>      Naive_pl;

// for polygon
#include "criticalcurves.h"

class Arrangement
{
public:
    Arrangement_2   arr;
    Arrangement();
    void addSeg(double,double,double,double);
    void addArc(double,double,double,double,double,double);
    void addCircle(double,double,double);
    void addOffset(Polygon,double);
    void addOffsets(std::list<Polygon>,double);
    void inRegion(double,double);
    void addOffsetScreen(int,int,double);
};

#endif
