#ifndef NONCRITICALREGION_H
#define NONCRITICALREGION_H

#include <list>
#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Arr_conic_traits_2.h>

typedef int Region_id;
typedef std::list<Region_id> Adjacent_region_list;
typedef CGAL::CORE_algebraic_number_traits Nt_traits;
typedef Nt_traits::Rational Rational;
typedef Nt_traits::Algebraic Algebraic;
typedef CGAL::Cartesian<Rational> Rat_kernel;
typedef CGAL::Cartesian<Algebraic> Alg_kernel;
typedef CGAL::Arr_conic_traits_2<Rat_kernel, Alg_kernel, Nt_traits> Conic_traits_2;
typedef Conic_traits_2::Point_2 Conic_point_2;
typedef std::list<int> Admissible_configuration_space_cell;
typedef std::list<Admissible_configuration_space_cell> Admissible_configuration_space_cells;


class NonCriticalRegion
{
protected:
    Region_id region_id;
    Adjacent_region_list adjacent_regions;
    Conic_point_2 point;
    Admissible_configuration_space_cells admissible_configuration_space_cells;
public:
    NonCriticalRegion();
    Region_id getRegionId();
    void setRegionId(Region_id region_id);
    void addAdjacentRegion(Region_id region_id);
    Conic_point_2 getPoint();
    void setPoint(Conic_point_2 point);
    Admissible_configuration_space_cells getAdmissibleConfigurationSpaceCells();
    void setAdmissibleConfigurationSpaceCells(Admissible_configuration_space_cells admissible_configuration_space_cells);
    ~NonCriticalRegion();
};

#endif // NONCRITICALREGION_H
