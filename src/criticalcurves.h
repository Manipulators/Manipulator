#ifndef CRITICALCURVES_H
#define CRITICALCURVES_H

#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Arr_conic_traits_2.h>
#include <CGAL/Arr_extended_dcel.h>
#include <CGAL/Arr_observer.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Gps_traits_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Qt/GraphicsItem.h>
#include "noncriticalregion.h"
#include <lemon/smart_graph.h>

typedef CGAL::CORE_algebraic_number_traits Nt_traits;
typedef Nt_traits::Rational Rational;
typedef Nt_traits::Algebraic Algebraic;
typedef CGAL::Cartesian<Rational> Rat_kernel;
typedef CGAL::Cartesian<Algebraic> Alg_kernel;
typedef CGAL::Arr_conic_traits_2<Rat_kernel, Alg_kernel, Nt_traits> Conic_traits_2;
typedef CGAL::Arr_extended_dcel<Conic_traits_2, int, int, lemon::SmartDigraph::Node> Dcel;
typedef CGAL::Arrangement_2<Conic_traits_2, Dcel> Arrangement_2;
typedef std::list<Arrangement_2> Arrangements_2;

typedef Arrangements_2::iterator Arrangement_2_iterator;
typedef Arrangement_2::Edge_iterator Edge_iterator;
typedef Arrangement_2::Face_handle Face_handle;


class CriticalCurves : public CGAL::Qt::GraphicsItem
{
    Q_OBJECT

public:
    // Critical curves.
    Arrangements_2 critical_curves;
    // Constructor.
    CriticalCurves();
    // Set the parameters of the critical curves and recompute them.
    void setParameters(double radius_1, double radius_2, Arrangements_2 inset_1, Arrangements_2 inset_2);
    // Get the arrangements representing the critical curves.
    Arrangements_2 getArrangements();
    // Clear the critical curves.
    void clear();
    // Receive changed signals from the critical curves instance.
    void modelChanged();
    // Get the bounding rectangle of the critical curves on the graphics scene.
    QRectF boundingRect() const;
    // Paint the critical curves on the graphics scene.
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    // Destructor.
    ~CriticalCurves();

protected:
    QRectF bounding_rect;
    void updateBoundingRect();

signals:
    void criticalCurvesChanged();
};

#endif
