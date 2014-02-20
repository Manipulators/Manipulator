#include "mainwindow.h"
#include <QApplication>


int main (int argc, char** argv)
{
    // Create Qt application.
    QApplication* application = new QApplication(argc, argv);

    // Create the main window.
    MainWindow* window = new MainWindow();

    // Show main window.
    window->show();

    // Open the input file.
    QStringList arguments = application->arguments();
    if (1 < arguments.size())
    {
        window->open(arguments.at(1));
    }

    // Enter the main event loop and wait for return value.
    return application->exec();
}
