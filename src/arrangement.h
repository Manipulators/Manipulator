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
#include "arr_print.h"

class Arrangement
{
public:
    Arrangement_2   arr;
    Arrangement();
    void addSeg(double,double,double,double);
    void addArc(double,double,double,double,double,double,double);
    void addCircle(double,double,double);
    void addOffset(Polygon,double);
    void addOffsets(std::list<Polygon>,double);
    int inRegion(double,double);
    void addOffsetScreen(int,int,double);
    void addCC2(Arrangement,double,Arrangement);
    void print();
};

//test
#include <CGAL/Object.h>

#include <boost/variant.hpp>

//-----------------------------------------------------------------------------
// Print the result of a point-location query.
//
template <class Arrangement_2>
int print_point_location(const typename Arrangement_2::Point_2& q,
                          CGAL::Object    obj)
{
  typename Arrangement_2::Vertex_const_handle    v;
  typename Arrangement_2::Halfedge_const_handle  e;
  typename Arrangement_2::Face_const_handle      f;

  //std::cout << "The point (" << q << ") is located ";
  if (CGAL::assign(f, obj))
  {
    // q is located inside a face:
    if (f->is_unbounded())
      {//std::cout << "inside the unbounded face." << std::endl;
    return 0;}
    else
      {//std::cout << "inside a bounded face." << std::endl;
    return 1;}
  }
  else if (CGAL::assign(e, obj))
  {
    // q is located on an edge:
    //std::cout << "on an edge: " << e->curve() << std::endl;
    return 1;
  }
  else if (CGAL::assign(v, obj))
  {

    // q is located on a vertex:
    /*if (v->is_isolated())
      //std::cout << "on an isolated vertex: " << v->point() << std::endl;
    else
      //std::cout << "on a vertex: " << v->point() << std::endl;*/
    return 1;
  }
  else
  {
    CGAL_error_msg( "Invalid object.");
  }
}


//-----------------------------------------------------------------------------
// Perform a point-location query and print the result.
//
template <class PointLocation>
int point_location_query(const PointLocation& pl,
                          const typename
                          PointLocation::Arrangement_2::Point_2& q)
{
  // Perform the point-location query.
  typedef PointLocation                                 Point_location;
  typedef typename Point_location::Arrangement_2        Arrangement_2;
  typename CGAL::Arr_point_location_result<Arrangement_2>::Type obj =
    pl.locate(q);

  // Print the result.
  return print_point_location<Arrangement_2>(q, obj);
}


#endif
