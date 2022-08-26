#ifndef MY_UNIQUE_PTR_H
#define MY_UNIQUE_PTR_H
#include <QMainWindow>

template<class T>
class my_unique_ptr
{
private:
    T * ptr = nullptr;
    void clean()
        {
            if (ptr != nullptr){
                delete ptr;
                ptr=nullptr;
            }
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


    my_unique_ptr(my_unique_ptr&& rhs)
    {
        ptr = rhs.ptr;
        rhs.ptr = nullptr;
    }

    my_unique_ptr& operator=(my_unique_ptr& dyingObj)
    {
        clean();
        ptr = std::move(dyingObj.ptr);
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
        delete ptr;
        ptr = ptr2;
    }


    void swap(my_unique_ptr& obj2)
    {
        std::swap(ptr, obj2.ptr);
    }

    bool operator_null()
    {
        if(ptr==nullptr) return 1;
        return 0;
    }

    T& operator*() const { return *ptr; }
    T* operator->() { return this->ptr; }
/*
    my_unique_ptr(my_unique_ptr&& dyingObj)
    {
        clean();
        ptr = std::move(dyingObj.ptr);
        dyingObj.ptr = nullptr;
    }
*/
};

#endif // MY_UNIQUE_PTR_H
