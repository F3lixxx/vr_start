#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.connected_devices();
    w.readOutput();
    w.show();
    return a.exec();
}
