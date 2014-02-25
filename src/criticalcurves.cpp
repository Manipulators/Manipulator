#include <QPainter>
#include <iterator>
#include"criticalcurves.h"

typedef Inset_polygons_2::iterator Inset_polygons_iterator;

// Define the CGAL elements of an inset polygon.
typedef Conic_traits_2::X_monotone_curve_2 X_monotone_curve_2;
typedef std::list<X_monotone_curve_2> Container;
typedef Container::iterator Curve_iterator;
typedef Arrangement_2::Edge_iterator Edge_iterator;


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


    typedef Rat_kernel::Point_2 Rat_point_2;
    typedef Rat_kernel::Segment_2 Rat_segment_2;
    typedef Rat_kernel::Circle_2 Rat_circle_2;
    typedef Conic_traits_2::Curve_2 Conic_arc_2;
    typedef Conic_traits_2::Point_2 Conic_point_2;

    // Add the critical curves of type I.
    // TODO: complete.
    for (Inset_polygons_iterator inset_polygon = this->inset_polygons.begin(); inset_polygon != this->inset_polygons.end(); ++inset_polygon)
    {
        for (Curve_iterator curve = inset_polygon->curves_begin(); curve != inset_polygon->curves_end(); ++curve)
        {
            if (CGAL::COLLINEAR == curve->orientation())
            {
                // Displaced a segment.
                // TODO: improve with the use of rational kernel operation (accuracy purpose).
                double factor = radius_1 + radius_2;
                Conic_point_2 source = curve->source();
                Conic_point_2 target = curve->target();
                double x_source = CGAL::to_double(source.x());
                double y_source = CGAL::to_double(source.y());
                double x_target = CGAL::to_double(target.x());
                double y_target = CGAL::to_double(target.y());
                double delta_x = x_target - x_source;
                double delta_y = y_target - y_source;
                double length = std::sqrt(delta_x * delta_x + delta_y * delta_y);
                double translation_x = factor * delta_y / length;
                double translation_y = - factor * delta_x / length;
                Rat_point_2 point_1(x_source + translation_x, y_source + translation_y);
                Rat_point_2 point_2(x_target + translation_x, y_target + translation_y);
                Rat_segment_2 segment(point_1, point_2);
                Conic_arc_2 conic_arc(segment);
                insert(this->critical_curves, conic_arc);
            }
            else
            {
                // Displaces an arc.
                // TODO: complete.

                Rational two = 2;
                Rational four = 4;

                Rational r = curve->r();
                Rational s = curve->s();
                Rational t = curve->t();
                Rational u = curve->u();
                Rational v = curve->v();
                Rational w_1 = curve->w();

                Rational r_1 = radius_1;
                Rational r_2 = radius_2;
                Rational r_3 = r_1 + two * r_2;

                Rational x_0 = - u / (two * r);
                Rational y_0 = - v / (two * r);
                Rational w_2 = r * ((u * u + v * v) / (four * r * r) - (r_3 * r_3));

                Conic_arc_2 conic_arc(r, s, t, u, v, w_2);
                //Conic_arc_2 conic_arc(r, s, t, u, v, w, CGAL::CLOCKWISE, source, target);
                insert(this->critical_curves, conic_arc);
            }
        }
    }

    // Add the critical curves of type II.
    // TODO: remove the curves which are not include in one of the inset polygons.
    for (Inset_polygons_iterator inset_polygon = this->inset_polygons.begin(); inset_polygon != this->inset_polygons.end(); ++inset_polygon)
    {
        for (Curve_iterator curve = inset_polygon->curves_begin(); curve != inset_polygon->curves_end(); ++curve)
        {
            int x = (int)(CGAL::to_double(curve->source().x()));
            int y = (int)(CGAL::to_double(curve->source().y()));
            double radius = radius_1 + radius_2;
            Rat_point_2 center(x, y);
            Rat_circle_2 circle(center, radius * radius);
            Conic_arc_2 conic_arc(circle);
            insert(this->critical_curves, conic_arc);
        }
    }

    // Remove the curves which are not include in one of the inset polygons.
    // TODO:complete.
    for (Edge_iterator edge = this->critical_curves.edges_begin(); edge != this->critical_curves.edges_end(); ++edge)
    {
        //zone(arrangment, curve, output_iterator);
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
