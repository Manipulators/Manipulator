#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QGraphicsView>
#include <QPainterPath>
#include <QPointF>
#include "mainwindow.h"


MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags),
    ui(new Ui::MainWindow)
{
    // Open the input files.
    std::ifstream in_file("../data/manipulator_1.data");

    // Read the width and height of the main window from the input file.
    int width;
    int height;
    in_file >> width;
    in_file >> height;

    // Read the barriers and the bodies from the input file.
    Barriers barriers;
    Bodie bodie1;
    Bodie bodie2;
    in_file >> barriers;
    in_file >> bodie1;
    in_file >> bodie2;
    in_file.close();

    // Display the barriers and the bodies on the standard input.
    barriers.print();
    bodie1.print();
    bodie2.print();

    this->setupUI();

    this->scene = new QGraphicsScene(this);
    this->ui->graphicsView->setScene(scene);

    this->addBarriers(barriers);
    this->addBodie(bodie1);
    this->addBodie(bodie2);

/*
    //Critical Graph(e) (cf Article for notations).
    Arrangement A1,A,S,CG;// critical graph;
    A1.addOffsets(obstacles.getPolygons(),robot1.r());
    A.addOffsets(obstacles.getPolygons(),robot2.r());
    CG.addOffsets(obstacles.getPolygons(),robot1.r()+2*robot2.r());
    S.addOffsetScreen(width, height,robot1.r());
*/
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

void MainWindow::addBarriers(Barriers barriers)
{
    this->scene->setBackgroundBrush(Qt::gray);
    QColor color = Qt::white;
    QPolygonF polygon_f = Polygon_CGAL_to_Qt(barriers.getPolygon());
    this->scene->addPolygon(polygon_f, QPen(color), QBrush(color));
    return;
}

void MainWindow::addBodie(Bodie bodie)
{
    Circle circle = bodie.getCircle();
    Point center = circle.center();
    double radius = circle.squared_radius();
    double diameter = 2.0 * radius;
    QColor color = Qt::darkBlue;
    this->scene->addEllipse(center.x() - radius, center.y() - radius, diameter, diameter, QPen(color), QBrush(color));
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


void MainWindow::on_actionQuit_triggered()
{
    qApp->exit();
    return;
}


void MainWindow::setupUI()
{
    this->ui->setupUi(this);
    return;
}
