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

/*void MainWindow::addArc(Node n1,Node nc,Node n2)
{//nc center; from point n1 to point n2 (counter clockwise); n1 must be on the circle
    double r =sqrt((n1.x - nc.x)*(n1.x - nc.x)+(n1.y - nc.y)*(n1.y - nc.y));
    QPainterPath* myPath = new QPainterPath();
    myPath->moveTo(QPointF(n1.x,n1.y));//Start point
    myPath->arcTo(QRectF(nc.x - r,nc.y - r,2*r,2*r),360 - angle1(n1.x-nc.x,n1.y-nc.y),360 - angle2(n1.x-nc.x,n1.y-nc.y,n2.x-nc.x,n2.y-nc.y));

    this->scene->addPath(*myPath,QPen(Qt::red));

    return;
}*/

void MainWindow::addLine(double x1, double y1, double x2, double y2)
{
    this->scene->addLine(x1,y1,x2,y2,QPen(Qt::red));
    return;
}

/*void MainWindow::addGraph(Graphe g)
{
    int i,j;
    for (i = 0; i < g.n - 1; i++)
    {
        for (j = i+1; j < g.n; j++)
        {
            Vertice v = ((g.matrix)[i][j]);
            switch (v.vtype)
            {
                case None:
                {
                    break;
                }
                case Seg:
                {
                    Node ni = (g.nodes)[i];
                    Node nj = (g.nodes)[j];
                    this->addLine(ni.x,ni.y,nj.x,nj.y);
                    break;
                }
                case Arc:
                {
                    Node ni = (g.nodes)[i];
                    Node nj = (g.nodes)[j];
                    Node nc;
                    nc.x = v.xc;
                    nc.y = v.yc;
                    this->addArc(nj,nc,ni);
                    break;
                }
            }
        }
    }
    return;
}*/

MainWindow::~MainWindow()
{
}
