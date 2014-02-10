#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QGraphicsView>
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
    double scene_height = (double)height - 24.0;
    this->scene = new QGraphicsScene(0.0, 0.0, scene_width, scene_height);
    QGraphicsView * view = new QGraphicsView(this->scene);
    this->setCentralWidget(view);
}

void MainWindow::addPolygon(Polygon polygon)
{
    QPolygonF polygon_f = Polygon_CGAL_to_Qt(polygon);
    this->scene->addPolygon(polygon_f, QPen(Qt::black), QBrush(Qt::darkBlue));
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

MainWindow::~MainWindow()
{
}
