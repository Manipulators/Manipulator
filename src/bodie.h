#ifndef BODIE_H
#define BODIE_H

#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Circle_2.h>
#include <CGAL/Point_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K ;
typedef CGAL::Circle_2<K>           Circle;
typedef CGAL::Point_2<K>           Point;


class Bodie
{
private:
    Circle circle;
public:
    // Constructor.
    Bodie();
    // Get the circle property of the bodie.
    Circle getCircle();
    // Set the circle property of the bodie.
    void setCircle(double, double, double, double, double);
    // Print a description of the bodie on the standard output.
    void print();
    // Final position.
    double xf;
    double yf;
    // Radius.
    double r();
    // Destructor.
    ~Bodie();
};

// Read the description of the bodie from the given stream.
std::istream & operator>>(std::istream &, Bodie &);

#endif // BODIE_H
