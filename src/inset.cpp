#include <CGAL/offset_polygon_2.h>
#include <QPainter>
#include "inset.h"

typedef Inset_polygons_2::iterator Inset_polygons_iterator;
typedef Conic_traits_2::X_monotone_curve_2 X_monotone_curve_2;
typedef std::list<X_monotone_curve_2> X_monotone_curves_2;
typedef X_monotone_curves_2::iterator X_monotone_curve_2_iterator;
typedef std::pair<double, double> approximated_point_2;


Inset::Inset()
{
    QObject::connect(this, SIGNAL(insetChanged()), this, SLOT(modelChanged()));
}

void Inset::setParameters(Polygon_2 polygon, double radius)
{
    Conic_traits_2 traits;
    inset_polygon_2(polygon, radius, traits, std::back_inserter(this->inset_polygons));
    emit(insetChanged());
    return;
}

Arrangements_2 Inset::getArrangements()
{
    int id = 1;
    Arrangements_2 arrangements;
    for (Inset_polygons_iterator inset_polygon = this->inset_polygons.begin(); inset_polygon != this->inset_polygons.end(); ++inset_polygon)
    {
        Arrangement_2 arrangement;
        for (X_monotone_curve_2_iterator curve = inset_polygon->curves_begin(); curve != inset_polygon->curves_end(); ++curve)
        {
            insert(arrangement, *curve);
        }
        for (Arrangement_2::Edge_iterator edge = arrangement.edges_begin(); edge != arrangement.edges_end(); ++edge)
        {
            // TODO: check if the labeling is correct (for successive x-monotone circle arcs or successive collinear segments).
            edge->set_data(id);
            edge->twin()->set_data(id++);
        }
        arrangements.push_back(arrangement);
    }
    return arrangements;
}

void Inset::modelChanged()
{
    updateBoundingRect();
    update(this->boundingRect());
    return;
}

QRectF Inset::boundingRect() const
{
    return this->bounding_rect;
}

void Inset::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    // Paint the inset polygons.
    for (Inset_polygons_iterator inset_polygon = this->inset_polygons.begin(); inset_polygon != this->inset_polygons.end(); ++inset_polygon)
    {
        for (X_monotone_curve_2_iterator curve = inset_polygon->curves_begin(); curve != inset_polygon->curves_end(); ++curve)
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

    return;
}

Inset::~Inset()
{
}

void Inset::updateBoundingRect()
{
    // TODO: improve.
    this->bounding_rect = QRectF(-300.0, -300.0, 600.0, 600.0);
}
