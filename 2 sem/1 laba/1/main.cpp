//9. Нарисовать самосвал, который может поднимать кузов.
// Родительский класс – перемещающийся прямоугольник.
#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(500,500);
    w.show();
    return a.exec();
}
