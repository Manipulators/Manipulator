#ifndef ROADMAP_H
#define ROADMAP_H

#include <list>
#include "criticalcurves.h"

typedef std::list<CGAL::Object> Objects;
typedef Arrangement_2::Face_handle Face_handle;
typedef Objects::iterator Object_iterator;

typedef Conic_traits_2::Point_2 Conic_point_2;
typedef Conic_traits_2::X_monotone_curve_2 Segment_2;

// compute euclidian distance
double disteucl(double, double, double, double);

int isInside (Arrangement_2, double, double, double, double);

int isOutside (Arrangement_2, double, double, double, double);

double frand(double, double);

class RoadMap
{
public:
    // Constructor
    RoadMap(Arrangement_2, double, double, double, double, Arrangement_2, double, double, double, double);
    // path = [source; x1; x2; ...; target]
    std::list< Conic_point_2 > path;
    // Destructor.
    ~RoadMap();
};

#endif
