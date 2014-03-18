#ifndef ROADMAP_H
#define ROADMAP_H

#include <list>
#include "criticalcurves.h"
#include <CGAL/Qt/GraphicsItem.h>

typedef std::list<CGAL::Object> Objects;
typedef Arrangement_2::Face_handle Face_handle;
typedef Objects::iterator Object_iterator;

typedef Conic_traits_2::Point_2 Conic_point_2;
typedef Conic_traits_2::X_monotone_curve_2 Segment_2;


// compute euclidian distance
double disteucl(double, double, double, double);

int isInside (Arrangement_2, double, double, double, double);

int isOutside (Arrangement_2, double, double, double, double);

double frand(double, double);

class RoadMap : public CGAL::Qt::GraphicsItem
{
    Q_OBJECT
public:
    // Constructor
    RoadMap();
    void set(Arrangement_2, Arrangement_2, double, double, double, double);
    // path = [source; x1; x2; ...; target]
    std::list< Conic_point_2 > path;

    // Receive changed signals from the main window.
    void modelChanged();
    // Get the bounding rectangle of the inset polygons on the GraphicsScene.
    QRectF boundingRect() const;
    // Paint the inset polygons on the GraphicsScene.
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    // Destructor.
    ~RoadMap();

protected:
    QRectF bounding_rect;
    void updateBoundingRect();

signals:
    void RoadMapChanged();
};

#endif
