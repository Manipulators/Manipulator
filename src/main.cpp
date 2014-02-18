#include "mainwindow.h"
#include <QApplication>


int main (int argc, char **argv)
{
    // Create Qt application.
    QApplication * application = new QApplication(argc, argv);

    // Create the main window.
    MainWindow * window = new MainWindow();

    // Show main window.
    window->show();

    // Enter the main event loop and wait for return value.
    return application->exec();
}
