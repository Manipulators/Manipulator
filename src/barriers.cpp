#include "barriers.h"


Barriers::Barriers()
{
}

Polygon Barriers::getPolygon()
{
    return this->polygon;
}

void Barriers::setPolygon(Polygon polygon)
{
    this->polygon = polygon;
}

void Barriers::print()
{
    std::cout << "Barriers" << std::endl;
    print_polygon(this->getPolygon());
}

void Barriers::modelChanged()
{
    update(Barriers::boundingRect());
    return;
}

QRectF Barriers::boundingRect() const
{
    return this->bounding_rect;
}

void Barriers::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QPolygonF polygon = Polygon_CGAL_to_Qt(this->polygon);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawPolygon(polygon);
    return;
}

Barriers::~Barriers()
{
}

std::istream& operator >>(std::istream& istream, Barriers* barriers)
{
    Polygon polygon;
    istream >> polygon;
    barriers->setPolygon(polygon);

    return istream;
}
