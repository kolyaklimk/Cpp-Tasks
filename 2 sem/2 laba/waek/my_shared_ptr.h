#ifndef MY_SHARED_PTR_H
#define MY_SHARED_PTR_H
#include <QMainWindow>

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
            count = nullptr;
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



#endif // MY_SHARED_PTR_H
