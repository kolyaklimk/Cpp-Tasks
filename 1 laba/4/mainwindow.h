#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <file.h>
#include <QComboBox>
#include <second.h>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, protected file
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void writte();

private slots:
    void on_radioButton_clicked();

    void on_pushButton_7_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    second *sWin;
    //file *da;
    int swit=0;

};
#endif // MAINWINDOW_H
