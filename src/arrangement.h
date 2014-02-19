#ifndef ARRANGEMENT_H
#define ARRANGEMENT_H

#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Arr_conic_traits_2.h>
#include <CGAL/offset_polygon_2.h>
#include <CGAL/General_polygon_2.h>
#include <iostream>
#include "polygon.h"

// Inset
typedef CGAL::CORE_algebraic_number_traits     Nt_traits;
typedef Nt_traits::Rational                    Rational;
typedef Nt_traits::Algebraic                   Algebraic;

struct Rat_kernel : public CGAL::Cartesian<Rational> {};
struct Alg_kernel : public CGAL::Cartesian<Algebraic> {};

typedef CGAL::Arr_conic_traits_2<Rat_kernel,Alg_kernel,Nt_traits>   Traits_2;
struct Conic_traits_2 : public Traits_2 {};

// General Polygon
typedef CGAL::Polygon_2<Rat_kernel>            Polygon_G;

typedef CGAL::Gps_traits_2<Conic_traits_2>     Gps_traits_2;
typedef Gps_traits_2::Polygon_2                Offset_polygon_2;

// Arrangement
#include <CGAL/Arrangement_2.h>
typedef Traits_2::Curve_2                               Conic_arc_2;
typedef CGAL::Arrangement_2<Traits_2>                   Arrangement_2;

class Arrangement
{
public:
    Arrangement_2   arr;
    // Constructor.
    Arrangement();
    // Add the inner offset of the polygon P in arr
    void addInsetPolygon (Polygon_G, double);

};

#endif
