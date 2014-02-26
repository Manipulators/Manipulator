#include <QPainter>
#include "inset.h"


Inset::Inset()
{
    QObject::connect(this, SIGNAL(insetChanged()), this, SLOT(modelChanged()));
}

void Inset::setParameters(Polygon_2 polygon, double radius_1, double radius_2)
{
    /*
    Conic_traits_2 traits;
    inset_polygon_2(polygon, radius_2, traits, std::back_inserter(this->inset_polygons));

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
    */
    return;
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
    typedef std::pair<double, double> approximated_point_2;

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

    return;
}

Inset::~Inset()
{
}

void Inset::updateBoundingRect()
{
    // TODO: improve.
    this->bounding_rect = QRectF(-200.0, -200.0, 400.0, 400.0);
}
