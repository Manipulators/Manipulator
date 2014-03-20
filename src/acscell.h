#ifndef ACSCELL_H
#define ACSCELL_H
#include <utility>
#include <list>
#include "graspcell.h"

class ACSCell
{
public:
    ACSCell();

    std::list<int> label;

    // Grasp Cells
    std::list<GraspCell> graspcells;

    ~ACSCell();
};

#endif // ACSCELL_H
