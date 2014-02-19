#include"arrangement.h"

Arrangement::Arrangement()
{
}

void Arrangement::addInsetPolygon (Polygon_G P, double r)
{//TODO : Convert a Polygon in a Polygon_G
  // Add the inner offset of the polygon P in arr
  Conic_traits_2                         traits;
  std::list<Offset_polygon_2>            inset_polygons;
  std::list<Offset_polygon_2>::iterator  iit;

  inset_polygon_2 (P, r, traits, std::back_inserter(inset_polygons));

  for (iit = inset_polygons.begin(); iit != inset_polygons.end(); ++iit)
  {
    CGAL:: insert_curves(this->arr,iit->curves_begin(),iit->curves_end());
    // Attention : insert_curves is a deprecated function
  };
  return;
}
