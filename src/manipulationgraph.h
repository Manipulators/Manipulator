#ifndef MANIPULATIONGRAPH_H
#define MANIPULATIONGRAPH_H

#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Qt/GraphicsItem.h>
#include <CGAL/Arr_conic_traits_2.h>
#include <CGAL/Arr_extended_dcel.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Arr_observer.h>
#include "noncriticalregion.h"

typedef CGAL::CORE_algebraic_number_traits Nt_traits;
typedef Nt_traits::Rational Rational;
typedef Nt_traits::Algebraic Algebraic;
typedef CGAL::Cartesian<Rational> Rat_kernel;
typedef CGAL::Cartesian<Algebraic> Alg_kernel;
typedef CGAL::Arr_conic_traits_2<Rat_kernel, Alg_kernel, Nt_traits> Conic_traits_2;
typedef CGAL::Arr_extended_dcel<Conic_traits_2, int, int, NonCriticalRegion*> Dcel;
typedef CGAL::Arrangement_2<Conic_traits_2, Dcel> Arrangement_2;
typedef std::list<Arrangement_2> Arrangements_2;


class Arrangement_2_observer : public CGAL::Arr_observer<Arrangement_2>
{
public:
    Arrangement_2_observer (Arrangement_2& arr) : CGAL::Arr_observer<Arrangement_2> (arr)
    {
    }

    virtual void after_split_edge (Halfedge_handle halfedge_1, Halfedge_handle halfedge_2)
    {
        int id_1 = halfedge_1->data();
        int id_2 = halfedge_2->data();
        int id_3 = halfedge_1->twin()->data();
        int id_4 = halfedge_2->twin()->data();
        int id = std::max(std::max(std::max(id_1, id_2), id_3), id_4);
        halfedge_1->set_data(id);
        halfedge_2->set_data(id);
        halfedge_1->twin()->set_data(id);
        halfedge_2->twin()->set_data(id);
    }
};

class ManipulationGraph : public CGAL::Qt::GraphicsItem
{
    Q_OBJECT

public:
    std::list<Conic_point_2> points;
    Arrangement_2 test;
    ManipulationGraph();
    void setParameters(double radius_1, double radius_2, Arrangements_2 inset_1, Arrangements_2 inset_2, Arrangements_2 critical_curves);
    void modelChanged();
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    ~ManipulationGraph();

protected:
    QRectF bounding_rect;
    void updateBoundingRect();

signals:
    void manipulationGraphChanged();
};

#endif // MANIPULATIONGRAPH_H
