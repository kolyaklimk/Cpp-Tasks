#ifndef MYDEQUE_H
#define MYDEQUE_H
#include <iostream>
#include <QDebug>
template <class T>
struct Elem{
    T* arr;
    int amout=0;
    int pos=0;
    int pos2=0;
    Elem* next, *prev;
};

template <class T>
class MyDeque{
private:
    Elem<T>* Head, *Tail;
    T* _MyDeque;
    int Size;
    int Count;
public:
    MyDeque(int Size){
        Head = Tail = NULL;
        Count = 0;
        this->Size=Size;
        if(Size<1) this->Size=1;
    }

    void insert(int pos, T v){
        if(pos == Count+1){
            push_back(v);
                return;
            }
        if(pos == 1){
            push_front(v);
            return;
        }
        *att(pos) = v;
    }

    ~MyDeque()
    {
        clear();
    }
    void clear(){
        while (Head != NULL) pop_back();
    }

    bool empty()
    {
        return Head == NULL;
    }

    int size()
    {
        return Count;
    }

    T back() {
        return Tail->arr[Tail->amout];
    }

    T front() {
        return Head->arr[0];
    }

    void resize(int a){
        MyDeque* buf = new MyDeque(a);
        Elem<T>* buf2=Head;
        if(a<=Size){
            while(buf2!=NULL){
                if(buf2->amout+1<=a){
                    for(int q=0;q<=buf2->amout;q++){
                        buf->push_back(buf2->arr[q]);
                    }
                    for(int q=buf2->amout+1;q<a;q++){
                        buf->push_back(0);
                    }
                }
                else{
                    for(int q=0;q<=a;q++){
                        buf->push_back(buf2->arr[q]);
                    }
                }
                buf2=buf2->next;
            }
        }
        else{
            while(buf2!=NULL){
                for(int q=0;q<=buf2->amout;q++){
                    buf->push_back(buf2->arr[q]);
                }
                for(int q=buf2->amout+1;q<a;q++){
                    buf->push_back(0);
                }
                buf2=buf2->next;
            }
        }
        clear();
        Head=buf->Head;
        Tail=buf->Tail;
        Size = a;
        Count = buf->Count;
    }

    T at(int a){
        T buf;
        Elem<T>* search = Head;
        while(a){
            for(int aa = 0; aa <= search->amout && a;aa++){
                a--;
                buf = search->arr[aa];
            }
            search=search->next;
        }
        return buf;
    }

    T* att(int a){
        T* buf;
        Elem<T>* search = Head;
        while(a){
            for(int aa = 0; aa <= search->amout && a;aa++){
                a--;
                buf = &search->arr[aa];
            }
            search=search->next;
        }
        return buf;
    }

    class Iterator{
    public:
        Iterator(T *ptr): _ptr(ptr){};
        ~Iterator(){};
        bool operator == (const Iterator& rhs) const
        {
            return _ptr == rhs._ptr;
        };

        bool operator != (const Iterator& rhs) const
        {
            return !(*this == rhs);
        };

        Iterator& operator = (const Iterator &rhs)
        {
            _ptr = rhs._ptr;
        };

        bool operator > (const Iterator &rhs)
        {
            return _ptr > rhs;
        };

        bool operator < (const Iterator &rhs)
        {
            return _ptr < rhs;
        };

        bool operator >= (const Iterator &rhs)
        {
            return _ptr >= rhs;
        };

        bool operator <= (const Iterator &rhs)
        {
            return _ptr <= rhs;
        };

        T operator + (const Iterator rhs)
        {
            return _ptr + rhs;
        };

        T operator - (const Iterator rhs)
        {
            return _ptr - rhs;
        };

        T operator += (const Iterator rhs)
        {
            return _ptr + rhs;
        };

        T operator -= (const Iterator rhs)
        {
            return _ptr - rhs;
        };

        T& operator*() const
        {
            return *_ptr;
        };

        T* operator->()
        {
            return _ptr;
        };

        T* operator&()
        {
            return _ptr;
        };

        Iterator& operator++()
        {
            _ptr++;
            return *this;
        }

        Iterator& operator--()
        {
            _ptr++;
            return *this;
        }

    private:
        T *_ptr = nullptr;
    };

    Iterator begins()
    {
        return att(1);
    }
    void push_back(T v){
    if(!Count){
        Head = Tail = new Elem<T>;
        Head->arr = new T[Size];
        Head->arr[Head->amout]=v;
        Head->next=NULL;
        Head->prev=NULL;
    }
    else{
        if(Tail->amout+1<Size){
            Tail->arr[++Tail->amout]=v;
        }
        else{
            Tail->next = new Elem<T>;
            Tail->next->prev=Tail;
            Tail = Tail->next;
            Tail->next = NULL;
            Tail->arr =new T[Size];
            Tail->arr[Tail->amout]=v;
        }
    }
    Count++;
    }


    void push_front(T v){
    if(!Count){
        Head = Tail = new Elem<T>;
        Head->arr = new T[Size];
        Head->arr[0]=v;
        Head->next=NULL;
        Head->prev=NULL;
    }
    else{
        if(Head->amout+1<Size){
            for(int a=Size-1;a>0;a--){
                Head->arr[a]=Head->arr[a-1];
            }
            Head->arr[0]=v;
            Head->amout++;
        }
        else{
            Head->prev = new Elem<T>;
            Head->prev->next=Head;
            Head = Head->prev;
            Head->prev = NULL;
            Head->arr =new T[Size];
            Head->arr[0]=v;
        }
    }
    Count++;
    }

    void pop_back(){

        if(Count == 1){
            delete Tail;
            Tail=Head=NULL;
        }
        else{
            if(!Tail->amout){
                delete Tail->arr;
                Tail=Tail->prev;
                delete Tail->next;
                Tail->next = NULL;
            }
            else{
                Tail->amout--;
            }
        }
        Count--;
    }

    void pop_front(){

        if(Count == 1){
            delete Tail;
            Tail=Head=NULL;
        }
        else{
            if(!Head->amout){
                delete Head->arr;
                Head=Head->next;
                delete Head->prev;
                Head->prev = NULL;
            }
            else{
                for(int a=0;a<Size-1;a++){
                    Head->arr[a]=Head->arr[a+1];
                }
                Head->amout--;
            }
        }
        Count--;
    }


    T& operator[](const int &index)
    {
        return at(index);
    }


    Iterator begin()
    {
        if(Size == 0)
            return nullptr;
        if(Count >1 )
            return att(Head->amout+1);
        return att(1);
    }
    Iterator end()
    {
        if(Size == 0)
            return nullptr;
        return att(Count);
    }

};
#endif // MYDEQUE_H
