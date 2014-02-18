#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <cmath>
#include "polygon.h"
#include "arrangement.h"
#include "criticalcurves.h"
#include "robot.h"


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
    // Add Line to the scene.
    void addLine(double, double, double, double);
    void addArc(double,double,double,double,double,double);
    //void addGraph(Graphe);
    void addRobot(Robot r);
    // Destructor.
    ~MainWindow();
};

#endif // MAINWINDOW_H

