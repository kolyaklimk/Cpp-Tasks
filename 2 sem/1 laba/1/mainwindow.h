#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <samosval.h>
#include <wheel.h>
#include <kuzov.h>
#include <QGraphicsScene>
#include <QTextBrowser>
#include <QString>
#include <QtMath>
#include <QTimer>
#include <QMouseEvent>
#include <windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void moving();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    samosval *item_samosval;
    wheel *item_wheel[3];
    kuzov *item_kuzov;
    void *item;

    double rotate=0, rotate_wheel1=93,rotate_wheel2=30,rotate_wheel3=63;
    int x1=100,x2=100,x3=149,x4=200,x5=278;
};

#endif // MAINWINDOW_H
