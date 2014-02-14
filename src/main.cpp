#include "mainwindow.h"
#include "robot.h"
#include "movableobject.h"
#include "obstacles.h"
#include "criticalcurves.h"
#include "graphe.h"
#include <QApplication>
#include <iostream>
#include <fstream>


int main (int argc, char **argv)
{
    // Create Qt application.
    QApplication app(argc, argv);

    // Open the input files.
    std::ifstream in_file("../data/manipulator_0.data");
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

    // Read the bodies from the input file (i.e. robot, movable object and obstacles).
    Robot robot1;
    Robot robot2;
    Obstacles obstacles;
    in_file >> robot1;
    in_file >> robot2;
    in_file >> obstacles;
    in_file.close();

    // Display the bodies.
    robot1.print();
    robot2.print();
    obstacles.print();

    //Critical Graph(e).
    Graphe graph;
    double r = 5;
    graph.addOffsets(obstacles.getPolygons(),r);
    graph.addOffsetScreen(width, height,r);

    // Show main window.
    MainWindow window(width, height);
    window.addRobot(robot1);
    window.addRobot(robot2);
    window.addPolygons(obstacles.getPolygons());
    window.addGraph(graph);
    window.show();

    // Enter the main event loop and wait for return value.
    return app.exec();
}
