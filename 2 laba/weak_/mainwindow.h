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
public:
    T * ptr = nullptr;
    uint * count = nullptr;
    void CleanAll(){
        if(count == nullptr) return;
        (*count)--;
        if (*count <= 0)
        {
            if (nullptr != ptr) delete ptr;
            delete count;
        }
    }


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
        //ptr=nullptr;
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





template<class T>
class my_weak_ptr
{
private:
    T * ptr = nullptr;
    uint count_shared = 0;

    void CleanAll(){
            if (nullptr != ptr) ptr =nullptr;
            count_shared=0;
    }

public:

    ~my_weak_ptr()
    {
        CleanAll();
    }
    my_weak_ptr() : ptr(nullptr) {}
    my_weak_ptr(T* ptr) : ptr(ptr){};

    my_weak_ptr(my_shared_ptr<T>& obj)
    {
        this->ptr = obj.ptr;
        this->count_shared = *obj.count;
        //obj.ptr = nullptr;
    }

    my_weak_ptr& operator = (my_shared_ptr<T>& obj)
    {
        CleanAll();
        this->ptr = obj.ptr;
        this->count_shared = *obj.count;
        //obj.ptr = nullptr;
    }

    my_weak_ptr(const my_weak_ptr& obj)
    {
        this->ptr = obj.ptr;
        obj.ptr = nullptr;
    }

    my_weak_ptr& operator = (const my_weak_ptr& obj)
    {
        CleanAll();
        this->ptr = obj.ptr;
        obj.ptr = nullptr;
    }
    uint use_count()
    {
        return count_shared;
    }

    void reset()
    {
        CleanAll();
    }

    void swap(my_weak_ptr& obj2)
    {
        using std::swap;
            swap(ptr, obj2.ptr);
    }

    void swap(my_shared_ptr<T>& obj2)
    {
        using std::swap;
            swap(ptr, obj2.ptr);
    }

    bool expired() {
        return (count_shared == 0);
    }

    bool owner_before(my_weak_ptr& obj)
    {
        if(&ptr>&obj.ptr) return 1;
        return 0;
    }

    my_shared_ptr<T> lock() {

        return my_shared_ptr<T>(ptr);
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
    void on_pushButton_5_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void draw_delete();
    void draw_t();

    void on_pushButton_6_clicked();

private:
    int xx=0;
    int xxx=0;
    int check_button=1;
    uint random(uint x);
    QTimer *timer;
    circle2* circlee2[2];
    QString str;
    QGraphicsScene* scene;
    QGraphicsScene* scene2;
    circle* circlee[3];
    line* linee[3];
    my_shared_ptr<circle> circle_ptr;
};
#endif // MAINWINDOW_H
