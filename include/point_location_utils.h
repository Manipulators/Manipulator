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

  std::cout << "The point (" << q << ") is located ";
  if (CGAL::assign(f, obj))
  {
    // q is located inside a face:
    if (f->is_unbounded())
      std::cout << "inside the unbounded face." << std::endl;
	return 0;
    else
      std::cout << "inside a bounded face." << std::endl;
	return 1;
  }
  else if (CGAL::assign(e, obj))
  {
    // q is located on an edge:
    std::cout << "on an edge: " << e->curve() << std::endl;
	return 1;
  }
  else if (CGAL::assign(v, obj))
  {
return 1;
    // q is located on a vertex:
    if (v->is_isolated())
      std::cout << "on an isolated vertex: " << v->point() << std::endl;
    else
      std::cout << "on a vertex: " << v->point() << std::endl;
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


