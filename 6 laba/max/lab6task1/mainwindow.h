#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "tree.h"
#include <QDialog>
#include <QSharedPointer>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void show_tree();

private slots:
    void on_add_clicked();

    void on_delete_2_clicked();

    void on_make_balanced_clicked();

    void on_show_bykey_clicked();

    //void on_obhod_clicked();

    void on_make_balanced_2_clicked();

    void on_add_2_clicked();

    void on_make_balanced_3_clicked();

    void on_make_balanced_4_clicked();

    void on_make_balanced_5_clicked();

    void on_make_balanced_6_clicked();

private:
    Ui::MainWindow *ui;

    taskTree<QString, int> tree;

    QDialog* wnd, *wnd_show;

    QLineEdit* inp, *inp_show;

};
#endif // MAINWINDOW_H
