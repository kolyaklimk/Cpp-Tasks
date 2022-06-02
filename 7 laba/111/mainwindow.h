#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "set.h"

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
    void on_find_clicked();

    void on_find_2_clicked();

    void on_find_3_clicked();

    void on_find_4_clicked();

private:

    void showw();

    Ui::MainWindow *ui;
    QVector<int> v;
    Set<int, QString> m;
};
#endif // MAINWINDOW_H
