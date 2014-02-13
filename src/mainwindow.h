#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include "polygon.h"
#include "graph.h"


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
    void addArc();
    void addGraph(Graph);
    // Destructor.
    ~MainWindow();
};

#endif // MAINWINDOW_H

