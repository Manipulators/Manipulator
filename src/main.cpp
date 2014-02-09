#include "mainwindow.h"
#include "robot.h"
#include "movableobject.h"
#include "obstacles.h"
#include <QApplication>
#include <iostream>
#include <fstream>


int main (int argc, char **argv)
{
    // Create Qt application.
    QApplication app(argc, argv);

    // Open the input files.
    std::ifstream in_file("../data/bodies.data");
    if (!in_file.is_open())
    {
        std::cerr << "Failed to open the input file." << std::endl;
        return (1);
    }

    // Read the bodies from the input file (i.e. robot, movable object and obstacles).
    Robot robot;
    MovableObject movable_object;
    Obstacles obstacles;
    in_file >> robot;
    in_file >> movable_object;
    in_file >> obstacles;
    in_file.close();

    // Show main window.
    MainWindow window;
    window.show();

    // Enter the main event loop and wait for return value.
    return app.exec();
}
