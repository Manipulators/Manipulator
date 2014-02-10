#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include "polygon.h"


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
    // Destructor.
    ~MainWindow();
};

#endif // MAINWINDOW_H

