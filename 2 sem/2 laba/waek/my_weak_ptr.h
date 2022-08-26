#ifndef MY_WEAK_PTR_H
#define MY_WEAK_PTR_H
#include <QMainWindow>
#include "my_shared_ptr.h"
#include <QDebug>
template<class T>
class my_weak_ptr
{
private:
    T * ptr = nullptr;
    uint * count = nullptr;
    uint *count_shared = nullptr;

    void CleanAll(){
            if (nullptr != ptr) ptr =nullptr;
            count_shared=0;

            if(count == nullptr) return;
            (*count)--;
            if (*count <= 0)
            {
                if (nullptr != ptr) ptr = nullptr;
                delete count;
                owner=0;
            }
    }

public:
    short owner;

    ~my_weak_ptr()
    {
        CleanAll();
    }
    my_weak_ptr() : ptr(nullptr),owner(1) {}
    my_weak_ptr(T* ptr) : ptr(ptr), count(new uint(1)),owner(1){};

    my_weak_ptr( my_shared_ptr<T>& obj)
    {
        this->ptr = obj.ptr;
        this->count_shared = obj.count;
        if (nullptr != obj.ptr) (*this->count)++;
        //obj.ptr = nullptr;
    }

    my_weak_ptr& operator = ( my_shared_ptr<T>& obj)
    {
        CleanAll();
        this->ptr = obj.ptr;
        this->count_shared = obj.count;
        if (nullptr != obj.ptr) (*this->count)++;
        //obj.ptr = nullptr;
    }

    my_weak_ptr(const my_weak_ptr& obj)
    {
        this->ptr = obj.ptr;
        this->count = obj.count;
        this->count_shared = obj.count_shared;
        if (nullptr != obj.ptr) (*this->count)++;
    }

    my_weak_ptr& operator = (const my_weak_ptr& obj)
    {
        CleanAll();
        this->ptr = obj.ptr;
        this->count = obj.count;
        this->count_shared = obj.count_shared;
        if (nullptr != obj.ptr) (*this->count)++;
        owner = *this->count;
    }

    uint use_count()
    {
        if(count_shared==nullptr) return 0;
        return *count_shared;
    }

    void reset()
    {
        CleanAll();
        owner=0;
    }

    void swap(my_weak_ptr& obj2)
    {
        std::swap(ptr, obj2.ptr);
        std::swap(owner, obj2.owner);
    }

    void swap(my_shared_ptr<T>& obj2)
    {
        std::swap(ptr, obj2.ptr);
    }

    bool expired() {
        return (count_shared == nullptr || !*count_shared);
    }

    bool owner_before(my_weak_ptr& obj)
    {
        if (!owner || !obj.owner) return 0;
        if(owner<obj.owner) return 1;
        return 0;
    }

    my_shared_ptr<T> lock() {

        return my_shared_ptr<T>(ptr);
    }

    T& operator*() const { return *ptr; }
    T* operator->() { return this->ptr; }
};

#endif // MY_WEAK_PTR_H
