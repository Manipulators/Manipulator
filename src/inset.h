#ifndef INSET_H
#define INSET_H

#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Arr_conic_traits_2.h>
#include <CGAL/Gps_traits_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Arr_extended_dcel.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Qt/GraphicsItem.h>
#include "noncriticalregion.h"
#include "criticalcurves.h"

typedef CGAL::Gps_traits_2<Conic_traits_2> Gps_traits_2;
typedef Gps_traits_2::Polygon_2 Inset_polygon_2;
typedef std::list<Inset_polygon_2> Inset_polygons_2;
typedef CGAL::Polygon_2<Rat_kernel> Polygon_2;


class Inset : public CGAL::Qt::GraphicsItem
{
    Q_OBJECT

public:
    // Inset polygons.
    Inset_polygons_2 inset_polygons;
    // Constructor.
    Inset();
    // Add the inner offset of the polygon P in arr.
    void setParameters(Polygon_2 polygon, double radius);
    // Get the arrangements representing the inset polygons.
    Arrangements_2 getArrangements();
    // Clear the inset polygons.
    void clear();
    // Receive changed signals from the main window.
    void modelChanged();
    // Get the bounding rectangle of the inset polygons on the GraphicsScene.
    QRectF boundingRect() const;
    // Paint the inset polygons on the GraphicsScene.
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    // Destructor.
    ~Inset();

protected:
    QRectF bounding_rect;
    void updateBoundingRect();

signals:
    void insetChanged();
};

#endif // INSET_H
