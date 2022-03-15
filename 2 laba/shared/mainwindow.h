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
class my_shared_ptr
{
private:
    T * ptr = nullptr;
    uint * count = nullptr;
    void CleanAll(){
        if(count == nullptr) return;
        (*count)--;
        if (*count == 0)
        {
            if (nullptr != ptr) delete ptr;
            delete count;
        }
    }

public:

    ~my_shared_ptr()
    {
        CleanAll();
    }
    my_shared_ptr() : ptr(nullptr) {}
    my_shared_ptr(T* ptr) : ptr(ptr), count(new uint(1)){};


    //копирование
    my_shared_ptr(const my_shared_ptr& obj)
    {
        this->ptr = obj.ptr;
        this->count = obj.count;
        if (nullptr != obj.ptr) (*this->count)++;
    }

    my_shared_ptr& operator = (const my_shared_ptr& obj)
    {
        CleanAll();
        this->ptr = obj.ptr;
        this->count = obj.count;
        if (nullptr != obj.ptr) (*this->count)++;
    }
    uint get_count() const { return *count; }

    T* get() const
    {
        return this->ptr;
    }

    void reset()
    {
        if (*count > 0) --(*count);
        if (count == 0) delete ptr;
        ptr=nullptr;
    }

    void swap(my_shared_ptr& obj2)
    {
        using std::swap;
            swap(ptr, obj2.ptr);
    }

    bool operator_null()
    {
        if(ptr==nullptr) return 1;
        return 0;
    }

    bool owner_before(my_shared_ptr& obj)
    {
        if(&ptr>&obj.ptr) return 1;
        return 0;
    }

    bool unique()
    {
    if(get_count()>1) return 0;
    return 1;
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
    circle* circlee[3];
    line* linee[3];
    my_shared_ptr<circle> circle_ptr;
};
#endif // MAINWINDOW_H
