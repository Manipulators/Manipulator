#include <QPainter>
#include "barriers.h"


Barriers::Barriers()
{
    QObject::connect(this, SIGNAL(barriersChanged()), this, SLOT(modelChanged()));
    updateBoundingBox();
}

Polygon_2 Barriers::getPolygon()
{
    return this->polygon;
}

void Barriers::setPolygon(Polygon_2 polygon)
{
    this->polygon = polygon;
    emit(barriersChanged());
    return;
}

void Barriers::modelChanged()
{
    updateBoundingBox();
    update(Barriers::boundingRect());
    return;
}

QRectF Barriers::boundingRect() const
{
    return this->bounding_rect;
}

void Barriers::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    typename Polygon_2::Vertex_iterator vertex;

    QPolygonF polygon;
    for (vertex = this->polygon.vertices_begin(); vertex != this->polygon.vertices_end(); ++vertex)
    {
        double x = CGAL::to_double(vertex->x());
        double y = CGAL::to_double(vertex->y());
        polygon << QPointF(x, y);
    }
    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawPolygon(polygon);
    return;
}

Barriers::~Barriers()
{
}

void Barriers::updateBoundingBox()
{
    if (!this->getPolygon().is_empty())
    {
        CGAL::Bbox_2 box = this->getPolygon().bbox();
        this->bounding_rect = QRectF(box.xmin(), box.ymin(), box.xmax() - box.xmin(), box.ymax() - box.ymin());
    }
    return;
}

std::istream& operator >>(std::istream& istream, Barriers* barriers)
{
    Polygon_2 polygon;
    istream >> polygon;
    barriers->setPolygon(polygon);

    return istream;
}
