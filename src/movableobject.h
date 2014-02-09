#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include <iostream>


class MovableObject
{
public:
    MovableObject();
    ~MovableObject();
};

std::istream & operator>>(std::istream &, MovableObject);

#endif // MOVABLEOBJECT_H
