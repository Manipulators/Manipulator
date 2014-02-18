#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QGraphicsView>
#include <QPainterPath>
#include <QPointF>
#include "mainwindow.h"


MainWindow::MainWindow(int width, int height, QWidget * parent)
{
    // Set some basic properties.
    this->setFixedWidth(width+20);
    this->setFixedHeight(height+40);
    this->setWindowTitle("Manipulator");

    // Set the menu bar.
    QMenuBar * menuBar = new QMenuBar(this);
    QMenu * fileMenu = new QMenu("File", menuBar);
    QAction * exitAction = new QAction("Exit", fileMenu);
    this->setMenuBar(menuBar);
    
    // Set the status bar.
    QStatusBar * statusBar = new QStatusBar();
    this->setStatusBar(statusBar);

    // Set the central widget with a scene.
    double scene_width = (double)width;
    double scene_height = (double)height;
    this->scene = new QGraphicsScene(0.0, 0.0, scene_width, scene_height);
    QGraphicsView * view = new QGraphicsView(this->scene);
    this->setCentralWidget(view);
}

void MainWindow::addPolygon(Polygon polygon)
{
    QPolygonF polygon_f = Polygon_CGAL_to_Qt(polygon);
    this->scene->addPolygon(polygon_f, QPen(Qt::black), QBrush(Qt::blue));
    return;
}

void MainWindow::addPolygons(std::list<Polygon> polygons)
{
    std::list<Polygon>::iterator polygon;
    for (polygon = polygons.begin(); polygon != polygons.end(); ++polygon)
    {
        this->addPolygon(* polygon);
    }
    return;
}

void MainWindow::addRobot(Robot r)
{
    Circle circle = r.get();
    Point c = circle.center();
    this->scene->addEllipse(c.x(),c.y(),circle.squared_radius(),circle.squared_radius(),QPen(Qt::green), QBrush(Qt::green));
    return;
}

void MainWindow::addArc(double xc,double yc,double x1,double y1,double x2,double y2)
{//nc center; from point n1 to point n2 (counter clockwise); n1 must be on the circle
    double r =sqrt((x1 - xc)*(x1 - xc)+(y1 - yc)*(y1 - yc));
    QPainterPath* myPath = new QPainterPath();
    myPath->moveTo(QPointF(x1,y1));//Start point
    myPath->arcTo(QRectF(xc - r,yc - r,2*r,2*r),360 - angle1(x1-xc,y1-yc),360 - angle2(x1-xc,y1-yc,x2-xc,y2-yc));

    this->scene->addPath(*myPath,QPen(Qt::red));

    return;
}

void MainWindow::addLine(double x1, double y1, double x2, double y2)
{
    this->scene->addLine(x1,y1,x2,y2,QPen(Qt::red));
    return;
}

MainWindow::~MainWindow()
{
}
