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
    // Scene slot.
    void viewChanged();
    void tabWidgetChanged();
    // File menu slots.
    void open(QString name);
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionQuit_triggered();

protected:
    Ui::MainWindow * ui;
    void setupUI();

private slots:
    void on_doubleSpinBoxInitialConfigurationFirstBodieX_valueChanged(double x);
    void on_doubleSpinBoxInitialConfigurationFirstBodieY_valueChanged(double y);
    void on_doubleSpinBoxInitialConfigurationSecondBodieX_valueChanged(double x);
    void on_doubleSpinBoxInitialConfigurationSecondBodieY_valueChanged(double y);
    void on_doubleSpinBoxFinalConfigurationFirstBodieX_valueChanged(double x);
    void on_doubleSpinBoxFinalConfigurationFirstBodieY_valueChanged(double y);
    void on_doubleSpinBoxFinalConfigurationSecondBodieX_valueChanged(double x);
    void on_doubleSpinBoxFinalConfigurationSecondBodieY_valueChanged(double y);
};

#endif // MAINWINDOW_H
