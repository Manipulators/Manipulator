#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
{
    int width = 600;
    int height = 400;
    setFixedWidth(width);
    setFixedHeight(height);
    setWindowTitle("Manipulator");

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu("File", menuBar);
    QAction *exitAction = new QAction("Exit", fileMenu);
    setMenuBar(menuBar);
    
    QStatusBar *statusBar = new QStatusBar();
    setStatusBar(statusBar);
}

MainWindow::~MainWindow()
{
}
