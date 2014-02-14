#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <cmath>
#include "polygon.h"
#include "graphe.h"
#include "criticalcurves.h"


class MainWindow : public QMainWindow
{
private:
    QGraphicsScene * scene;
public:
    // Constructor.
    MainWindow(int, int, QWidget * parent = 0);
    // Add a polygon to the scene.
    void addPolygon(Polygon);
    // Add a list of polygons to the scene.
    void addPolygons(std::list<Polygon>);
    // Add circle to the scene.
    void addCircle(double, double, double);
    // Add Line to the scene.
    void addLine(double, double, double, double);
    void addArc(Node,Node,Node);
    void addGraph(Graphe);
    // Destructor.
    ~MainWindow();
};

#endif // MAINWINDOW_H

