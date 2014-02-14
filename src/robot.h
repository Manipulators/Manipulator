#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Circle_2.h>
#include <CGAL/Point_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K ;
typedef CGAL::Circle_2<K>           Circle;
typedef CGAL::Point_2<K>           Point;


class Robot
{
private:
    Circle circle;
public:
    // Constructor.
    Robot();
    // Get the circle property of the robot.
    Circle get();
    // Set the circle property of the robot.
    void set(double,double,double);
    // Print a description of the robot on the standard output.
    void print();
    // Destructor.
    ~Robot();
};

// Read the description of the robot from the given stream.
std::istream & operator>>(std::istream &, Robot &);

#endif // ROBOT_H
