#include "mainwindow.h"
#include "barriers.h"
#include "bodie.h"
#include "criticalcurves.h"
#include <QApplication>
#include <iostream>
#include <fstream>


int main (int argc, char **argv)
{
    // Create Qt application.
    QApplication app(argc, argv);

    // Open the input files.
    std::ifstream in_file("../data/manipulator_1.data");
    if (!in_file.is_open())
    {
        std::cerr << "Failed to open the input file." << std::endl;
        return (1);
    }

    // Read the width and height of the main window from the input file.
    int width;
    int height;
    in_file >> width;
    in_file >> height;

    // Read the barriers and the bodies from the input file.
    Barriers barriers;
    Bodie bodie1;
    Bodie bodie2;
    in_file >> barriers;
    in_file >> bodie1;
    in_file >> bodie2;
    in_file.close();

    // Display the bodies.
    barriers.print();
    bodie1.print();
    bodie2.print();

    /*
    //Critical Graph(e) (cf Article for notations).
    Arrangement A1,A,S,CG;// critical graph;
    A1.addOffsets(obstacles.getPolygons(),robot1.r());
    A.addOffsets(obstacles.getPolygons(),robot2.r());
    CG.addOffsets(obstacles.getPolygons(),robot1.r()+2*robot2.r());
    S.addOffsetScreen(width, height,robot1.r());
    */

    // Show main window.
    MainWindow window(width, height);
    window.addBarriers(barriers);
    window.addBodie(bodie1);
    window.addBodie(bodie2);
    //window.addPolygons(obstacles.getPolygons());
    window.show();

    // Enter the main event loop and wait for return value.
    return app.exec();
}
