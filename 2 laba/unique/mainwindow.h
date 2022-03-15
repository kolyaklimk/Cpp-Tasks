#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "circle.h"
#include "circle2.h"
#include "line.h"
#include <QDebug>
#include <QThread>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

template<class T>
class my_unique_ptr
{
private:
    T * ptr = nullptr;
    void clean()
        {
            if (ptr != nullptr)
                delete ptr;
        }

public:

    ~my_unique_ptr()
    {
        clean();
    }
    my_unique_ptr() : ptr(nullptr) {}
    my_unique_ptr(T* ptr) : ptr(ptr){};

    my_unique_ptr(const my_unique_ptr& obj) = delete;

    my_unique_ptr& operator=(const my_unique_ptr& obj) = delete;


    my_unique_ptr(my_unique_ptr& dyingObj)
    {
        clean();
        this->ptr = dyingObj.ptr;
        dyingObj.ptr = nullptr;
    }

    my_unique_ptr& operator=(my_unique_ptr& dyingObj)
    {
        clean();
        this->ptr = dyingObj.ptr;
        dyingObj.ptr = nullptr;
    }

    T* get() const
    {
        return this->ptr;
    }

    T* get_deleter()
    {
        clean();
    }

    T* release()
    {
        T* ans = ptr;
        ptr = nullptr;
        return ans;
    }

    void reset(T* ptr2 = nullptr)
    {
        T* old = ptr;
        ptr = ptr2;
        delete old;
    }


    void swap(my_unique_ptr& obj2)
    {
        using std::swap;
            swap(ptr, obj2.ptr);
    }

    bool operator_null()
    {
        if(ptr==nullptr) return 1;
        return 0;
    }

    T& operator*() const { return *ptr; }
    T* operator->() { return this->ptr; }
};




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void draw_delete();
    void draw_t();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    int xx=0;
    int xxx=0;
    int check_button=1;
    uint random(uint x);
    QTimer *timer;
    circle2* circlee2;
    QString str;
    QGraphicsScene* scene;
    QGraphicsScene* scene2;
    my_unique_ptr<circle> circle_ptr;
    circle* circlee[3];
    line* linee[3];
};
#endif // MAINWINDOW_H
