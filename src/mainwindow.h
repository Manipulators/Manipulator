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
#include "ui_MainWindow.h"


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QGraphicsScene *scene;
    QString filename;
    Barriers *barriers;
    Bodie *bodie_1;
    Bodie *bodie_2;

public:
    // Constructor.
    MainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);
    // Add a line to the scene.
    void addLine(double, double, double, double);

    //void addArc(Node,Node,Node);
    //void addGraph(Graphe);

    // Destructor.
    ~MainWindow();

public slots:
    // File menu slots.
    void open(QString name);
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionQuit_triggered();

signals:
    void changed();

protected:
    Ui::MainWindow * ui;
    void setupUI();
};

#endif // MAINWINDOW_H
