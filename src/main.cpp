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
    Robot robot;
    MovableObject movable_object;
    Obstacles obstacles;
    in_file >> robot;
    in_file >> movable_object;
    in_file >> obstacles;
    in_file.close();

    // Display the bodies.
    robot.print();
    movable_object.print();
    obstacles.print();

    //Critical Graph(e).
    Graphe graph;
    graph.addOffsets(offsets(obstacles.getPolygons(),5));

    // Show main window.
    MainWindow window(width, height);
    window.addPolygon(robot.getPolygon());
    window.addPolygon(movable_object.getPolygon());
    window.addPolygons(obstacles.getPolygons());
    window.addGraph(graph);
    window.show();

    // Enter the main event loop and wait for return value.
    return app.exec();
}
