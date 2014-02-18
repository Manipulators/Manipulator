#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <cmath>
#include <iostream>
#include <fstream>
#include "polygon.h"
#include "barriers.h"
#include "bodie.h"
#include "arrangement.h"
#include "criticalcurves.h"


class MainWindow : public QMainWindow
{
private:
    QGraphicsScene * scene;
public:
    // Constructor.
    MainWindow(QWidget * parent = 0);
    // Add a polygon to the scene.
    void addPolygon(Polygon);
    // Add a list of polygons to the scene.
    void addPolygons(std::list<Polygon>);
    // Add a line to the scene.
    void addLine(double, double, double, double);
    // Add some barriers to the scene.
    void addBarriers(Barriers);
    // Add a bodie to the scene.
    void addBodie(Bodie);

    //void addArc(Node,Node,Node);
    //void addGraph(Graphe);

    // Destructor.
    ~MainWindow();
};

#endif // MAINWINDOW_H

