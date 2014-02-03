#include <QApplication>
#include <QWidget>


int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    // Create a window
    QWidget window;
    window.setFixedSize(600, 400);
    window.setWindowTitle("Manipulator");
    window.show();

    return application.exec();
}
