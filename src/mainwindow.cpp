#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QGraphicsView>
#include <QPainterPath>
#include "mainwindow.h"


MainWindow::MainWindow(int width, int height, QWidget * parent)
{
    // Set some basic properties.
    this->setFixedWidth(width);
    this->setFixedHeight(height);
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
    double scene_width = (double)width - 2.0;
    double scene_height = (double)height - 24.0;//Can't see everything !!!
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

void MainWindow::addCircle(double x, double y, double r)
{
    this->scene->addEllipse(x,y,r,r,QPen(Qt::red));
    return;
}

/* TODO : void MainWindow::addArc()
{
    QPainterPath* path = new QPainterPath();
    path->arcMoveTo(0,0,50,50,20);
    path->arcTo(0,0,50,50,20, 90);

    this->scene->addPath(*path,QPen(Qt::red));
    return;
}*/

void MainWindow::addLine(double x1, double y1, double x2, double y2)
{
    this->scene->addLine(x1,y1,x2,y2,QPen(Qt::red));
    return;
}

void MainWindow::addGraph(Graphe g)
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
                    this->addLine(ni.x,ni.y,nj.x,nj.y);
                    break;
                }
            }
        }
    }
    return;
}

MainWindow::~MainWindow()
{
}
