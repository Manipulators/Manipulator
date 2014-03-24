#ifndef ACSCELL_H
#define ACSCELL_H
#include <utility>
#include <list>
#include "graspcell.h"

#include <CGAL/Arr_conic_traits_2.h>
#include <CGAL/Arr_extended_dcel.h>
#include <CGAL/Arr_observer.h>
#include <CGAL/Arrangement_2.h>

typedef CGAL::CORE_algebraic_number_traits Nt_traits;
typedef Nt_traits::Rational Rational;
typedef Nt_traits::Algebraic Algebraic;
typedef CGAL::Cartesian<Rational> Rat_kernel;
typedef CGAL::Cartesian<Algebraic> Alg_kernel;
typedef CGAL::Arr_conic_traits_2<Rat_kernel, Alg_kernel, Nt_traits> Conic_traits_2;
typedef CGAL::Arr_extended_dcel<Conic_traits_2, int, int, lemon::SmartDigraph::Node> Dcel;
typedef CGAL::Arrangement_2<Conic_traits_2, Dcel> Arrangement_2;
typedef std::list<Arrangement_2> Arrangements_2;

typedef Arrangements_2::iterator Arrangement_2_iterator;
typedef Arrangement_2::Edge_iterator Edge_iterator;
typedef Arrangement_2::Face_handle Face_handle;

class ACSCell
{
public:
    // Constructor
    ACSCell();

    // The ACS cell label
    std::list<int> label;

    // Arrangement containing the ACS cell
    Arrangement_2 arrangement;

    // Grasp Cells associated to a ACE cell
    std::list<GraspCell> graspcells;

    // Destructor
    ~ACSCell();
};

#endif // ACSCELL_H
