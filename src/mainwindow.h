#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include "polygon.h"


class MainWindow : public QMainWindow
{
private : QGraphicsScene *scene;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addText(char * text);
    void addPolygon(Polygon);
};

#endif // MAINWINDOW_H

