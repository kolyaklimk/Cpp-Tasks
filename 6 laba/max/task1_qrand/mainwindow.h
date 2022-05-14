#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QInputDialog>
#include <QMessageBox>

#include <iostream>

#include "hashtable.hpp"
#include "myexception.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAdd_triggered();

    void on_actionErase_triggered();

    void on_actionCount_triggered();

    void on_actionAdd_random_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    hashtable<int> ht;
    void updateText();
    vector<int> v;
};

#endif // MAINWINDOW_H
