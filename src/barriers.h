#ifndef BARRIERS_H
#define BARRIERS_H

#include <CGAL/CORE_algebraic_number_traits.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Qt/GraphicsItem.h>

typedef CGAL::CORE_algebraic_number_traits Nt_traits;
typedef Nt_traits::Rational Rational;
typedef CGAL::Cartesian<Rational> Rat_kernel;
typedef CGAL::Polygon_2<Rat_kernel> Polygon_2;


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
    // Receive changed signals from the barriers instance.
    void modelChanged();
    // Get the bounding rectangle of one bodie on the graphics scene.
    QRectF boundingRect() const;
    // Paint the barriers on the graphics scene.
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    // Destructor.
    ~Barriers();

signals:
    void barriersChanged();

protected:
    QRectF bounding_rect;
    void updateBoundingBox();
};

// Read the description of the barriers from the given stream.
std::istream& operator >> (std::istream& stream, Barriers* barriers);

#endif // BARRIERS_H
