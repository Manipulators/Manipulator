#ifndef NONCRITICALREGION_H
#define NONCRITICALREGION_H

#include <list>
#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Arr_conic_traits_2.h>
#include "acscell.h"

typedef CGAL::CORE_algebraic_number_traits Nt_traits;
typedef Nt_traits::Rational Rational;
typedef Nt_traits::Algebraic Algebraic;
typedef CGAL::Cartesian<Rational> Rat_kernel;
typedef CGAL::Cartesian<Algebraic> Alg_kernel;
typedef CGAL::Arr_conic_traits_2<Rat_kernel, Alg_kernel, Nt_traits> Conic_traits_2;
typedef Conic_traits_2::Point_2 Conic_point_2;


class NonCriticalRegion
{
public:
    NonCriticalRegion();

    Conic_point_2 point;
    std::list<ACSCell> acscells;

    ~NonCriticalRegion();
};

#endif // NONCRITICALREGION_H