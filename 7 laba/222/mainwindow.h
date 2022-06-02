#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "unordered_map.h"

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
    void on_pushButton_clicked();

    void on_deploy_clicked();

    void on_add_clicked();

    void on_deploy_2_clicked();

    void on_deploy_4_clicked();

    void on_deploy_3_clicked();

private:

    void show_set();

    Ui::MainWindow *ui;

    unordered_map<int, QString> s;
};
#endif // MAINWINDOW_H
