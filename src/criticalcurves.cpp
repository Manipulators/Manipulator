#include <QPainter>
#include <iterator>
#include"criticalcurves.h"

typedef Inset_polygons_2::iterator Inset_polygons_iterator;

// Define the CGAL elements of an inset polygon.
typedef Conic_traits_2::X_monotone_curve_2 X_monotone_curve_2;
typedef std::list<X_monotone_curve_2> Container;
typedef Container::iterator Curve_iterator;


CriticalCurves::CriticalCurves()
{
    // TODO: improve.
    this->bounding_rect = QRectF(-300.0, -300.0, 500.0, 500.0);
    QObject::connect(this, SIGNAL(criticalCurvesChanged()), this, SLOT(modelChanged()));
}

void CriticalCurves::setParameters(Polygon_2 polygon, double radius_1, double radius_2)
{
    Conic_traits_2 traits;
    inset_polygon_2(polygon, radius_2, traits, std::back_inserter(this->inset_polygons));


// TODO: compute the critical curves of class I and II in an arrangment. ///////

    // Add the curves of the inset polygons.
    for (Inset_polygons_iterator inset_polygon = this->inset_polygons.begin(); inset_polygon != this->inset_polygons.end(); ++inset_polygon)
    {
        for (Curve_iterator curve = inset_polygon->curves_begin(); curve != inset_polygon->curves_end(); ++curve)
        {
            insert(this->critical_curves, *curve);
        }
    }

    // Add the critical curves of type I.
    // TODO: complete.
    for (Inset_polygons_iterator inset_polygon = this->inset_polygons.begin(); inset_polygon != this->inset_polygons.end(); ++inset_polygon)
    {

    }

    // Add the critical curves of type II.
    // TODO: complete.

    typedef Rat_kernel::Point_2 Rat_point_2;
    typedef Rat_kernel::Circle_2 Rat_circle_2;
    typedef Conic_traits_2::Curve_2 Conic_arc_2;

    for (Inset_polygons_iterator inset_polygon = this->inset_polygons.begin(); inset_polygon != this->inset_polygons.end(); ++inset_polygon)
    {
        for (Curve_iterator curve = inset_polygon->curves_begin(); curve != inset_polygon->curves_end(); ++curve)
        {
            int x = (int)(CGAL::to_double(curve->source().x()));
            int y = (int)(CGAL::to_double(curve->source().y()));
            double radius = radius_1 + radius_2;
            Rat_circle_2 circle (Rat_point_2(x, y), radius * radius);
            Conic_arc_2 conic_arc (circle);
            insert(this->critical_curves, conic_arc);
        }
    }

////////////////////////////////////////////////////////////////////////////////


    emit(criticalCurvesChanged());
    return;
}

void CriticalCurves::clear()
{
    this->inset_polygons.clear();
    return;
}

void CriticalCurves::modelChanged()
{
    updateBoundingRect();
    update(this->boundingRect());
    return;
}

QRectF CriticalCurves::boundingRect() const
{
    return this->bounding_rect;
}

void CriticalCurves::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    typedef std::pair<double, double> approximated_point_2;

/* Do not delete, temporarily commented. ***************************************

    // Paint the inset polygons.

    for (Inset_polygons_iterator inset_polygon = this->inset_polygons.begin(); inset_polygon != this->inset_polygons.end(); ++inset_polygon)
    {
        for (Curve_iterator curve = inset_polygon->curves_begin(); curve != inset_polygon->curves_end(); ++curve)
        {
            // TODO: improve the number of points used for the approximation..
            int n = 25;
            approximated_point_2* points = new approximated_point_2[n + 1];
            curve->polyline_approximation(n, points);
            if (CGAL::COLLINEAR == curve->orientation())
            {
                // Draw a segment.
                QPointF p1 = QPointF(points[0].first, points[0].second);
                QPointF p2 = QPointF(points[1].first, points[1].second);
                painter->drawLine(p1, p2);
            }
            else
            {
                // Draw an approximation of the conic arc.
                QPainterPath path;
                path.moveTo(points[0].first, points[0].second);
                for (int i = 1; i < n + 1; ++i)
                {
                    path.lineTo(points[i].first, points[i].second);
                }
                painter->drawPath(path);
            }
        }
    }

*******************************************************************************/


    // Paint the critical curves.

    typedef Arrangement_2::Edge_iterator Edge_iterator;

    for (Edge_iterator edge = this->critical_curves.edges_begin(); edge != this->critical_curves.edges_end(); ++edge)
    {
        // TODO: improve the number of points used for the approximation..
        int n = 25;
        double point_size = 0.5;
        approximated_point_2* points = new approximated_point_2[n + 1];
        edge->curve().polyline_approximation(n, points);
        if (CGAL::COLLINEAR == edge->curve().orientation())
        {
            // Draw a segment.
            QPointF p1 = QPointF(points[0].first, points[0].second);
            QPointF p2 = QPointF(points[1].first, points[1].second);
            painter->drawLine(p1, p2);
            // Draw its endpoints.
            QPointF p3 = QPointF(points[0].first, points[0].second);
            QPointF p4 = QPointF(points[1].first, points[1].second);
            painter->setBrush(QBrush(Qt::black));
            painter->drawEllipse(p3, point_size, point_size);
            painter->drawEllipse(p4, point_size, point_size);
            painter->setBrush(QBrush(Qt::transparent));
        }
        else
        {
            // Draw an approximation of the conic arc.
            QPainterPath path;
            path.moveTo(points[0].first, points[0].second);
            for (int i = 1; i < n + 1; ++i)
            {
                path.lineTo(points[i].first, points[i].second);
            }
            painter->drawPath(path);
            // Draw its endpoints.
            QPointF p3 = QPointF(points[0].first, points[0].second);
            QPointF p4 = QPointF(points[n].first, points[n].second);
            painter->setBrush(QBrush(Qt::black));
            painter->drawEllipse(p3, point_size, point_size);
            painter->drawEllipse(p4, point_size, point_size);
            painter->setBrush(QBrush(Qt::transparent));
        }
    }

    return;
}

CriticalCurves::~CriticalCurves()
{
}

void CriticalCurves::updateBoundingRect()
{
    // TODO: improve.
    this->bounding_rect = QRectF(-200.0, -200.0, 400.0, 400.0);
}
