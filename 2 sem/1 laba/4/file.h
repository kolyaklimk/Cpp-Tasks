#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QVector>
#include <QDate>
#include <QDebug>
#include <QFileDialog>

class file
{
protected:
    file();
    bool read();
    void write();
    void sort();
    void delet(int);
    void store();
    void store_save();
    int sizee=0;
    QVector<QString> name_project;
    QVector<QString> work_of_project;
    QVector<QString> name_worker;
    QVector<QString> name_direct;
    QVector<QDate> date_of_issue;
    QVector<QDate> deadline;
    QVector<QDate> date_delivery;
    QString storage;
};

#endif // FILE_H
