#include <CGAL/offset_polygon_2.h>
#include <QPainter>
#include "criticalcurves.h"


typedef Conic_traits_2::Point_2 Conic_point_2;
typedef Rat_kernel::Point_2 Rat_point_2;
typedef Conic_traits_2::Curve_2 Conic_arc_2;
typedef Conic_traits_2::X_monotone_curve_2 X_monotone_curve_2;
typedef Alg_kernel::FT Algebraic_ft;
typedef Rat_kernel::Circle_2 Rat_circle_2;
typedef std::list<CGAL::Object> Objects;
typedef Objects::iterator Object_iterator;

typedef std::pair<double, double> approximated_point_2;



CriticalCurves::CriticalCurves()
{
    QObject::connect(this, SIGNAL(criticalCurvesChanged()), this, SLOT(modelChanged()));
}

void CriticalCurves::setParameters(double radius_1, double radius_2, Arrangements_2 insets_1, Arrangements_2 insets_2)
{
    Arrangement_2_iterator inset_1 = insets_1.begin();
    Arrangement_2_iterator inset_2 = insets_2.begin();

    while (inset_1 != insets_1.end() && inset_2 != insets_2.end())
    {
        Arrangement_2 arrangement;

        // Add the curves of the inset.
        for (Edge_iterator edge = inset_1->edges_begin(); edge != inset_1->edges_end(); ++edge)
        {
            insert(arrangement, edge->curve());
        }

        // Add the critical curves of type I.
        for (Edge_iterator edge = inset_2->edges_begin(); edge != inset_2->edges_end(); ++edge)
        {
            if (CGAL::COLLINEAR == edge->curve().orientation())
            {
                // Displaced a segment.
                Nt_traits nt_traits;
                Algebraic_ft factor = nt_traits.convert(Rational(radius_1) + Rational(radius_2));
                Conic_point_2 source = edge->curve().source();
                Conic_point_2 target = edge->curve().target();
                Algebraic_ft delta_x = target.x() - source.x();
                Algebraic_ft delta_y = target.y() - source.y();
                Algebraic_ft length = nt_traits.sqrt(delta_x * delta_x + delta_y * delta_y);
                Algebraic_ft translation_x = factor * delta_y / length;
                Algebraic_ft translation_y = - factor * delta_x / length;
                Conic_point_2 point_1(source.x() + translation_x, source.y() + translation_y);
                Conic_point_2 point_2(target.x() + translation_x, target.y() + translation_y);
                Algebraic_ft a = - delta_y;
                Algebraic_ft b = delta_x;
                Algebraic_ft c = factor * length - (source.y() * target.x() - source.x() * target.y());
                X_monotone_curve_2 x_monotone_curve(a, b, c, point_1, point_2);
                insert(arrangement, x_monotone_curve);
            }
            else
            {
                // Displaces an arc.
                Rational two(2);
                Rational four(4);

                Rational r = edge->curve().r();
                Rational s = edge->curve().s();
                Rational t = edge->curve().t();
                Rational u = edge->curve().u();
                Rational v = edge->curve().v();
                Rational w = edge->curve().w();

                Nt_traits nt_traits;
                Rational x_center = - u / (two * r);
                Rational y_center = - v / (two * r);
                Rat_point_2 rat_center(x_center, y_center);
                Conic_point_2 center(nt_traits.convert(x_center), nt_traits.convert(y_center));

                Rational radius = Rational(radius_1) + two * Rational(radius_2);

                Algebraic_ft coefficient = nt_traits.convert(radius / Rational(radius_2));

                Conic_point_2 source_1 = edge->curve().source();
                Algebraic_ft x_source_2 = center.x() + coefficient * (source_1.x() - center.x());
                Algebraic_ft y_source_2 = center.y() + coefficient * (source_1.y() - center.y());
                Conic_point_2 source_2(x_source_2, y_source_2);

                Conic_point_2 target_1 = edge->curve().target();
                Algebraic_ft x_target_2 = center.x() + coefficient * (target_1.x() - center.x());
                Algebraic_ft y_target_2 = center.y() + coefficient * (target_1.y() - center.y());
                Conic_point_2 target_2(x_target_2, y_target_2);

                Rat_circle_2 circle(rat_center, radius * radius);

                Conic_arc_2 conic_arc(circle, CGAL::COUNTERCLOCKWISE, source_2, target_2);

                insert(arrangement, conic_arc);
            }
        }

        // Add the critical curves of type II.
        for (Edge_iterator edge = inset_2->edges_begin(); edge != inset_2->edges_end(); ++edge)
        {
            double x = CGAL::to_double(edge->curve().source().x());
            double y = CGAL::to_double(edge->curve().source().y());
            double radius = radius_1 + radius_2;
            Rat_point_2 center(x, y);
            Rat_circle_2 circle(center, radius * radius);
            Conic_arc_2 conic_arc(circle);
            insert(arrangement, conic_arc);
        }

        // Remove the curves which are not include in the inset.
        Objects objects;
        Face_handle face;
        for (Edge_iterator edge = arrangement.edges_begin(); edge != arrangement.edges_end(); ++edge)
        {
            CGAL::zone(*inset_1, edge->curve(), std::back_inserter(objects));
            for (Object_iterator object = objects.begin(); object != objects.end(); ++object)
            {
                if (assign(face, *object))
                {
                    if (face->is_unbounded())
                    {
                        remove_edge(arrangement, edge);
                        break;
                    }
                }
            }
            objects.clear();
        }

        // Print essential information on the standard input.
        std::cout << "Arrangement:" << std::endl;
        std::cout << "  Number of vertices: " << arrangement.number_of_vertices() << std::endl;
        std::cout << "  Number of edges   : " << arrangement.number_of_edges() << std::endl;
        std::cout << "  Number of face    : " << arrangement.number_of_faces() << std::endl;

        this->critical_curves.push_back(arrangement);

        ++inset_1;
        ++inset_2;
    }

    // Commit changes.
    emit(criticalCurvesChanged());
    return;
}

Arrangements_2 CriticalCurves::getArrangements()
{
    return this->critical_curves;
}

void CriticalCurves::clear()
{
    this->critical_curves.clear();
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
    // Paint the critical curves.
    for (Arrangement_2_iterator arrangement = this->critical_curves.begin(); arrangement != this->critical_curves.end(); ++arrangement)
    {
        for (Edge_iterator edge = arrangement->edges_begin(); edge != arrangement->edges_end(); ++edge)
        {
            // TODO: improve the number of points used for the approximation..
            int n = 25;
            /* Temporarily commented.
            double point_size = 0.4;
            */
            approximated_point_2* points = new approximated_point_2[n + 1];
            edge->curve().polyline_approximation(n, points);
            if (CGAL::COLLINEAR == edge->curve().orientation())
            {
                // Draw a segment.
                QPointF p1 = QPointF(points[0].first, points[0].second);
                QPointF p2 = QPointF(points[1].first, points[1].second);
                painter->drawLine(p1, p2);
                /* Temporarily commented.
                // Draw its endpoints.
                QPointF p3 = QPointF(points[0].first, points[0].second);
                QPointF p4 = QPointF(points[1].first, points[1].second);
                painter->setBrush(QBrush(Qt::black));
                painter->drawEllipse(p3, point_size, point_size);
                painter->drawEllipse(p4, point_size, point_size);
                painter->setBrush(QBrush(Qt::transparent));
                */
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
                /* Temporarily commented.
                // Draw its endpoints.
                QPointF p3 = QPointF(points[0].first, points[0].second);
                QPointF p4 = QPointF(points[n].first, points[n].second);
                painter->setBrush(QBrush(Qt::black));
                painter->drawEllipse(p3, point_size, point_size);
                painter->drawEllipse(p4, point_size, point_size);
                painter->setBrush(QBrush(Qt::transparent));
                */
            }
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
    this->bounding_rect = QRectF(-300.0, -300.0, 600.0, 600.0);
}
