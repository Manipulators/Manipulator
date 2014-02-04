#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication qApplication(argc, argv);

    // Create the main window
    MainWindow main_window;
    main_window.show();

    return qApplication.exec();
}
