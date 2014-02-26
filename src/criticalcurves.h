#ifndef CRITICALCURVES_H
#define CRITICALCURVES_H

#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Arr_conic_traits_2.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Gps_traits_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Qt/GraphicsItem.h>

typedef CGAL::CORE_algebraic_number_traits Nt_traits;
typedef Nt_traits::Rational Rational;
typedef Nt_traits::Algebraic Algebraic;
typedef CGAL::Cartesian<Rational> Rat_kernel;
typedef CGAL::Cartesian<Algebraic> Alg_kernel;
typedef CGAL::Arr_conic_traits_2<Rat_kernel, Alg_kernel, Nt_traits> Conic_traits_2;
typedef CGAL::Arrangement_2<Conic_traits_2> Arrangement_2;
typedef std::list<Arrangement_2> Arrangements_2;


class CriticalCurves : public CGAL::Qt::GraphicsItem
{
    Q_OBJECT

public:
    // Critical curves.
    Arrangements_2 critical_curves;
    // Constructor.
    CriticalCurves();
    // Set the parameters of the critical curves and recompute them.
    void setParameters(Arrangements_2 inset, double radius_1, double radius_2);
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
