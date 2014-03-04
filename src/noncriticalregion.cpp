#include "noncriticalregion.h"

NonCriticalRegion::NonCriticalRegion()
{
}

Region_id NonCriticalRegion::getRegionId()
{
    return this->region_id;
}

void NonCriticalRegion::setRegionId(Region_id region_id)
{
    this->region_id = region_id;
    return;
}

void NonCriticalRegion::addAdjacentRegion(Region_id region_id)
{
    this->adjacent_regions.push_back(region_id);
}

Conic_point_2 NonCriticalRegion::getPoint()
{
    return this->point;
}

void NonCriticalRegion::setPoint(Conic_point_2 point)
{
    this->point = point;
    return;
}

Admissible_configuration_space_cells NonCriticalRegion::getAdmissibleConfigurationSpaceCells()
{
    return this->admissible_configuration_space_cells;
}

void NonCriticalRegion::setAdmissibleConfigurationSpaceCells(Admissible_configuration_space_cells admissible_configuration_space_cells)
{
    this->admissible_configuration_space_cells = admissible_configuration_space_cells;
    return;
}

NonCriticalRegion::~NonCriticalRegion()
{
}
