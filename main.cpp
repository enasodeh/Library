#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Library Management System - COS2614 Assignment 3");
    w.resize(900, 600);
    w.show();
    return a.exec();
}
