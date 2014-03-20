#ifndef GRASPCELL_H
#define GRASPCELL_H

#include <utility>
#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Arr_conic_traits_2.h>
#include <lemon/smart_graph.h>

typedef lemon::SmartDigraph SmartDigraph;

typedef CGAL::CORE_algebraic_number_traits Nt_traits;
typedef Nt_traits::Rational Rational;
typedef Nt_traits::Algebraic Algebraic;
typedef CGAL::Cartesian<Rational> Rat_kernel;
typedef CGAL::Cartesian<Algebraic> Alg_kernel;
typedef CGAL::Arr_conic_traits_2<Rat_kernel, Alg_kernel, Nt_traits> Conic_traits_2;
typedef Conic_traits_2::Point_2 Conic_point_2;

class GraspCell
{
public:
    GraspCell();

    int label1;
    int label2;
    SmartDigraph::Node node;
    // Point for robot
    Conic_point_2 point;

    ~GraspCell();
};

#endif // GRASPCELL_H
