#ifndef OBSTACLES_H
#define OBSTACLES_H

#include <iostream>


class Obstacles
{
public:
    Obstacles();
    ~Obstacles();
};

std::istream & operator>>(std::istream &, Obstacles);

#endif // OBSTACLES_H
