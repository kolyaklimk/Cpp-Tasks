#ifndef MY_SHARED_PTR_H
#define MY_SHARED_PTR_H
#include <QMainWindow>
#include <qdebug.h>
template<class T>
class my_shared_ptr
{
private:
    T * ptr = nullptr;
    uint * count = nullptr;
    void CleanAll();

public:
    short owner;

    ~my_shared_ptr();
    my_shared_ptr();
    my_shared_ptr(T* ptr);


    //копирование
    my_shared_ptr(const my_shared_ptr& obj);

    my_shared_ptr& operator = (const my_shared_ptr& obj);

    uint get_count() const ;

    T* get() const;

    void reset();

    void swap(my_shared_ptr& obj2);

    bool operator_null();

    bool owner_before(my_shared_ptr& obj);

    bool unique();


    T& operator*() const;
    T* operator->();
};

template<class T>
void my_shared_ptr<T>::CleanAll(){
    if(count == nullptr) return;
    if (ptr==nullptr && *count) return;
    (*count)--;
    if (*count == 0)
    {
        if (nullptr != ptr) delete ptr;
        delete count;
        owner=0;
    }
}

template<class T>
my_shared_ptr<T>::~my_shared_ptr()
{
    CleanAll();
}

template<class T>
my_shared_ptr<T>::my_shared_ptr() : ptr(nullptr),owner(1) {}

template<class T>
my_shared_ptr<T>::my_shared_ptr(T* ptr) : ptr(ptr), count(new uint(1)), owner(1){}

template<class T>
my_shared_ptr<T>::my_shared_ptr(const my_shared_ptr& obj)
{
    this->ptr = obj.ptr;
    this->count = obj.count;
    if (nullptr != obj.ptr) (*this->count)++;
    //owner = *this->count;
}

template<class T>
my_shared_ptr<T>& my_shared_ptr<T>::operator = (const my_shared_ptr& obj)
{
    CleanAll();
    this->ptr = obj.ptr;
    this->count = obj.count;
    if (nullptr != obj.ptr) (*this->count)++;
    owner = *this->count;
}

template<class T>
uint my_shared_ptr<T>::get_count() const { return *count; }

template<class T>
T* my_shared_ptr<T>::get() const
{
    return this->ptr;
}

template<class T>
void my_shared_ptr<T>::reset()
{
    if (*count > 0) --(*count);
    if (count == 0) delete ptr;
    ptr=nullptr;
    owner=0;
}

template<class T>
void my_shared_ptr<T>::swap(my_shared_ptr& obj2)
{
    using std::swap;
        swap(ptr, obj2.ptr);
}

template<class T>
bool my_shared_ptr<T>::operator_null()
{
    if(ptr==nullptr) return 1;
    return 0;
}

template<class T>
bool my_shared_ptr<T>::owner_before(my_shared_ptr& obj)
{
    if (!owner || !obj.owner) return 0;
    if(owner<obj.owner) return 1;
    return 0;
}


template<class T>
bool my_shared_ptr<T>::unique()
{
if(get_count()>1) return 0;
return 1;
}

template<class T>
T& my_shared_ptr<T>::operator*() const { return *ptr; }

template<class T>
T* my_shared_ptr<T>::operator->() { return this->ptr; }


#endif // MY_SHARED_PTR_H
