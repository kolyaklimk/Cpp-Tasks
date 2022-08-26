#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QProcess>
#include <QMainWindow>
#include <QGraphicsScene>
#include <circle.h>
#include <square.h>
#include <triangle.h>
#include <rectangle.h>
#include <star_5.h>
#include <star_6.h>
#include <star_8.h>
#include <pentagon.h>
#include <hexagon.h>
#include <romb.h>
#include <dot.h>
#include <custom.h>
#include <QTextBrowser>
#include <QString>
#include <QtMath>
#include <QTimer>
#include <QMouseEvent>
//#include <QGraphicsItemAnimation>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:
    double xx=0;
    double yy=0;
    double radius=100;
    double center_x;
    double center_y;

    int rotat;

    int figur = 0;
    int fx=260, fy=210;
    int dx=260, dy=210;
    int buf,buf2,buf3=0;
    int bufx=dx, bufy=dy, buf2x=dx, buf2y=dy;
    double buf4=1,buf5;
    bool check_button=0;
    void scen();

private slots:
    void on_radioButton_2_clicked();
    void on_radioButton_clicked();

    //масштаб
    void on_pushButton_2_clicked();
    void pushButton_2_clicked();
    void trans_re_pushButton_2_clicked();
    void re_pushButton_2_clicked();

    //вращение
    void on_pushButton_clicked();
    void pushButton_clicked();
    void re_pushButton_clicked();
    void trans_re_pushButton_clicked();

    //точка
    void on_down_clicked();
    void on_up_clicked();
    void on_right_clicked();
    void on_left_clicked();
    void on_sbros_clicked();

    void down_clicked();
    void up_clicked();
    void right_clicked();
    void left_clicked();


    //объект
    void on_up_2_clicked();
    void on_down_2_clicked();
    void on_left_2_clicked();
    void on_right_2_clicked();
    void on_sbros_2_clicked();

    void up_2_clicked();
    void down_2_clicked();
    void left_2_clicked();
    void right_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_9_clicked();

    void on_radioButton_10_clicked();

private:
    void delete_figurs(int x);
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    circle *item_circle;
    square *item_square;
    triangle *item_triangle;
    romb *item_romb;
    star_5 *item_star_5;
    star_6 *item_star_6;
    star_8 *item_star_8;
    rectangle *item_rectangle;
    pentagon *item_pentagon;
    hexagon *item_hexagon;
    dot *d;
    QPoint widgetPos;

    //QGraphicsItemAnimation *anim;
};
#endif // MAINWINDOW_H
