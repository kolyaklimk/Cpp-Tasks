#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QIODevice>
#include <QFile>
#include <QDebug>
#include <QStandardItemModel>
#include <QDialog>
#include <QDate>
#include <QFileDialog>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class Date{
public:
    bool data();
    void store();
    QString NextDay(QString);
    int raznica(QString,QString);
    QString PreviousDay(QString);
    bool IsLeap(QString);
    short WeekNumber(QString);
    int DaysTillYourBithday(QString);
    int Duration(QString);
    int strok=0;
    QVector<QString> dat;
    QVector<QString> dat_next;
    QString bithdaydate;
    QString storage;
private:
    QStandardItemModel *model;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void table();

private slots:
    void on_tomorrow_clicked();

    void on_yesterday_clicked();

    void on_higher_year_clicked();

    void on_Weeks_clicked();

    void on_days_to_birsd_clicked();

    void on_pushButton_clicked();

    void on_change_clicked();

    void on_delete_2_clicked();

    void on_change_2_clicked();

    void on_days_to_birsd_2_clicked();

private:
    Ui::MainWindow *ui;
    Date *da;
    QStandardItemModel *model;
};
#endif // MAINWINDOW_H
