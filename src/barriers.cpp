#include <CGAL/Bbox_2.h>
#include "barriers.h"


Barriers::Barriers()
{
    QObject::connect(this, SIGNAL(barriersChanged()), this, SLOT(modelChanged()));
    updateBoundingBox();
}

Polygon Barriers::getPolygon()
{
    return this->polygon;
}

void Barriers::setPolygon(Polygon polygon)
{
    this->polygon = polygon;
    emit(barriersChanged());
    return;
}

void Barriers::print()
{
    std::cout << "Barriers:" << std::endl;
    print_polygon(this->getPolygon());
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
    QPolygonF polygon = Polygon_CGAL_to_Qt(this->polygon);
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
    Polygon polygon;
    istream >> polygon;
    barriers->setPolygon(polygon);

    return istream;
}
