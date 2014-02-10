#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QWidget>
#include <QGraphicsScene>

class MainWindow : public QMainWindow
{
private : QGraphicsScene *scene;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addText(char * text);
};

#endif // MAINWINDOW_H

