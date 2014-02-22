#ifndef BODIE_H
#define BODIE_H

#include <iostream>
#include <CGAL/Qt/GraphicsItem.h>


class Bodie : public CGAL::Qt::GraphicsItem
{
    Q_OBJECT

private:
    double x;
    double y;
    double r;

public:
    // Constructor.
    Bodie();
    // Get the radius property of the bodie.
    double getR();
    // Set the radius property of the bodie.
    void setR(double r);
    // Get the x-coordinate of the bodie.
    double getX();
    // Set the x-coordinate of the bodie.
    void setX(double x);
    // Get the x-coordinate of the bodie.
    double getY();
    // Set the y-coordinate of the bodie.
    void setY(double y);
    // Print a description of the bodie on the standard output.
    void print();
    // Final position.
    double xf;
    double yf;

    // Receive changed signals from the main window.
    void modelChanged();
    // Get the bounding rectangle of one bodie on the GraphicsScene.
    QRectF boundingRect() const;
    // Paint one bodie on the GraphicsScene.
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    // Destructor.
    ~Bodie();

signals:
    void bodieChanged();

protected:
    QRectF bounding_rect;
    void updateBoundingRect();
};

// Read the description of the bodie from the given stream.
std::istream& operator >>(std::istream& stream, Bodie* bodie);

#endif // BODIE_H
