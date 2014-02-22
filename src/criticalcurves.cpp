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
    this->bounding_rect = QRectF(-200.0, -200.0, 400.0, 400.0);
    QObject::connect(this, SIGNAL(criticalCurvesChanged()), this, SLOT(modelChanged()));
}

void CriticalCurves::addInsetPolygon (Polygon_2 P, double r)
{
    Conic_traits_2 traits;
    inset_polygon_2(P, r, traits, std::back_inserter(this->inset_polygons));
    emit(criticalCurvesChanged());
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
    // TODO: improve.
    for (Inset_polygons_iterator inset_polygon = this->inset_polygons.begin(); inset_polygon != this->inset_polygons.end(); ++inset_polygon)
    {
        for (Curve_iterator curve = inset_polygon->curves_begin(); curve != inset_polygon->curves_end(); ++curve)
        {
            int n = 1;
            typedef std::pair<double, double> approximated_point_2;
            approximated_point_2* points = new approximated_point_2[n + 1];
            curve->polyline_approximation(n, points);
            for (int i = 0; i < n; ++i)
            {
                QPoint source = QPoint(points[i + 0].first, points[i + 0].second);
                QPoint target = QPoint(points[i + 1].first, points[i + 1].second);
                painter->drawLine(source, target);
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
    this->bounding_rect = QRectF(-200.0, -200.0, 400.0, 400.0);
}
