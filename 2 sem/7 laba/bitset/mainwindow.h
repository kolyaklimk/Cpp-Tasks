#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "bitset.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void show_bitset();

private slots:
    void on_flip__clicked();

    void on_all__clicked();

    void on_any__clicked();

    void on_test__clicked();

    void on_set__clicked();

    void on_reset__clicked();

    void on_set_1_clicked();

    void on_set_2_clicked();

    void on_set_3_clicked();

private:
    Ui::MainWindow *ui;

    bitset<sizeof (int)*4> b;
};
#endif // MAINWINDOW_H
