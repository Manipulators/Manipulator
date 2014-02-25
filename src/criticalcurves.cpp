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
    Arrangement_2 inset_polygons;
    for (Inset_polygons_iterator inset_polygon = this->inset_polygons.begin(); inset_polygon != this->inset_polygons.end(); ++inset_polygon)
    {
        for (Curve_iterator curve = inset_polygon->curves_begin(); curve != inset_polygon->curves_end(); ++curve)
        {
            insert(inset_polygons, *curve);
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

                typedef Alg_kernel::FT Algebraic_ft;

                Rational two(2);
                Rational four(4);

                Rational r = curve->r();
                Rational s = curve->s();
                Rational t = curve->t();
                Rational u = curve->u();
                Rational v = curve->v();
                Rational w = curve->w();

                Nt_traits nt_traits;
                Rational x_center = - u / (two * r);
                Rational y_center = - v / (two * r);
                Rat_point_2 rat_center(x_center, y_center);
                Conic_point_2 center(nt_traits.convert(x_center), nt_traits.convert(y_center));

                Rational radius = Rational(radius_1) + two * Rational(radius_2);

                Algebraic_ft coefficient = nt_traits.convert(radius / Rational(radius_2));

                Conic_point_2 source_1 = curve->source();
                Algebraic_ft x_source_2 = center.x() + coefficient * (source_1.x() - center.x());
                Algebraic_ft y_source_2 = center.y() + coefficient * (source_1.y() - center.y());
                Conic_point_2 source_2(x_source_2, y_source_2);

                Conic_point_2 target_1 = curve->target();
                Algebraic_ft x_target_2 = center.x() + coefficient * (target_1.x() - center.x());
                Algebraic_ft y_target_2 = center.y() + coefficient * (target_1.y() - center.y());
                Conic_point_2 target_2(x_target_2, y_target_2);

                Rat_circle_2 circle(rat_center, radius * radius);

                Conic_arc_2 conic_arc(circle, CGAL::COUNTERCLOCKWISE, source_2, target_2);

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

    typedef Arrangement_2::Face_handle Face_handle;
    typedef std::list<CGAL::Object> Objects;
    typedef Objects::iterator Object_iterator;

    Objects objects;
    Face_handle face;
    for (Edge_iterator edge = this->critical_curves.edges_begin(); edge != this->critical_curves.edges_end(); ++edge)
    {
        CGAL::zone(inset_polygons, edge->curve(), std::back_inserter(objects));
        for (Object_iterator object = objects.begin(); object != objects.end(); ++object)
        {
            if (assign(face, *object))
            {
                if (face->is_unbounded())
                {
                        remove_edge(this->critical_curves, edge);
                        break;
                }
            }
        }
        objects.clear();
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
