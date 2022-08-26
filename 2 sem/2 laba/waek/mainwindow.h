#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "my_weak_ptr.h"
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_clicked();

    void on_delete_2_clicked();


    void on_add_2_clicked();

    void on_delete_3_clicked();

    //void on_reset_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QList<my_weak_ptr<int>> lem;
    QList<my_shared_ptr<int>> shared;
    int* l;
    QVector<char> rand;
    void reform(int);
};
#endif // MAINWINDOW_H
