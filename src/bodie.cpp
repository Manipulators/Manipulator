#include <QPainter>
#include "bodie.h"


Bodie::Bodie()
{
    this->x = 0;
    this->y = 0;
    this->r = 0;
    QObject::connect(this, SIGNAL(bodieChanged()), this, SLOT(modelChanged()));
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
    painter->drawPoint(0, 0);
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
        bodie->xf=xf;
        bodie->yf=yf;
    }
    return istream;
}
