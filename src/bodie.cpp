#include "bodie.h"

Bodie::Bodie()
{
    this->x = 0;
    this->y = 0;
    this->r = 0;
    QObject::connect(this, SIGNAL(bodieChanged()), this, SLOT(modelChanged()));
}

Circle Bodie::getCircle()
{
    return this->circle;
}

double Bodie::getRadius()
{
    Circle circle = this->getCircle();
    return circle.squared_radius();
}

double Bodie::getR()
{
    return this->r;
}

void Bodie::setR(double r)
{
    if (!(this->r == r))
    {
        this->r = r;
        emit(bodieChanged());
    }
    return;
}

double Bodie::getX()
{
    return this->x;
}

void Bodie::setX(double x)
{
    if (!(this->x == x))
    {
        this->x = x;
        emit(bodieChanged());
    }
    return;
}

double Bodie::getY()
{
    return this->y;
}

void Bodie::setY(double y)
{
    if (!(this->y == y))
    {
        this->y = y;
        emit(bodieChanged());
    }
    return;
}

void Bodie::setCircle(double x, double y, double r, double xf, double yf)
{
    this->circle = Circle(Point(x,y), r);
    this->xf = xf;
    this->yf = yf;
    emit(bodieChanged());
    return;
}

void Bodie::print()
{
    Circle circle = this->getCircle();
    Point c = circle.center();
    std::cout << "Bodie:" << std::endl;
    std::cout << "[center: ("<< c.x() << " " << c.y() << "), radius: " << circle.squared_radius() << "]" << std::endl;
}

void Bodie::modelChanged()
{
    updateBoundingRect();
    this->setPos(this->getX(), this->getY());
    return;
}

QRectF Bodie::boundingRect() const
{
    return this->bounding_rect;
}

void Bodie::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    double r = (int)this->getR();
    double d = 2 * r;
    painter->setPen(Qt::black);
    painter->setBrush(Qt::darkBlue);
    painter->drawEllipse(-r, -r, d, d);
    return;
}

Bodie::~Bodie()
{
}

void Bodie::updateBoundingRect()
{
    double r = this->getR();
    double d = 2 * r;
    this->bounding_rect = QRectF(-r,-r, d, d);
    return;
}

std::istream& operator >>(std::istream& istream, Bodie* bodie)
{
    if (istream)
    {
        double xi, yi, r, xf, yf;
        istream >> xi;
        istream >> yi;
        istream >> r;
        istream >> xf;
        istream >> yf;

        bodie->setR(r);
        bodie->setX(xi);
        bodie->setY(yi);
        bodie->setCircle(xi, yi, r, xf, yf);
    }
    return istream;
}
