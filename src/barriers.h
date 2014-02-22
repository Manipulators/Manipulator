#ifndef BARRIERS_H
#define BARRIERS_H

#include "polygon.h"
#include <CGAL/Qt/GraphicsItem.h>
#include <iostream>


class Barriers : public CGAL::Qt::GraphicsItem
{
    Q_OBJECT

private:
    Polygon_2 polygon;

public:
    // Constructor.
    Barriers();
    // Get the polygon property of the barriers.
    Polygon_2 getPolygon();
    // Set the polygon property of the barriers.
    void setPolygon(Polygon_2 polygon);
    // Print a description of the barriers on the standard output.
    void print();

    void modelChanged();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // Destructor.
    ~Barriers();

signals:
    void barriersChanged();

protected:
    QRectF bounding_rect;
    void updateBoundingBox();
};

// Read the description of the barriers from the given stream.
std::istream& operator >>(std::istream& stream, Barriers* barriers);

#endif // BARRIERS_H
