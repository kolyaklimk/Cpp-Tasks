#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

template <class T>
struct Elem {
    T value;
    Elem* next;
};

template <class T>
class Queue
{
    Elem<T>* Head, Tail;
    int Count;
public:
    Queue()
    {
        Head = Tail = NULL;
        Count = 0;
    }

    ~Queue()
    {
        while (Head != NULL) pop();
    }

    int size()
    {
        return Count;
    }


    void push(T v)
    {
        if (Count == 0) {
            Head = Tail = new Elem<T>;
            Head->next = NULL;
        }
        else {
            Tail->next = new Elem<T>;
            Tail = Tail->next;
            Tail->next = NULL;
        }
        Tail->value = v;
        Count++;
    }

    void pop()
    {
        if (Head->next != NULL) {
            Elem<T>*del = Head;
            Head = Head->next;
            delete del;
        }
        else {
            delete Head;
            Head = NULL;
            Tail = NULL;
        }
        Count--;
    }

    void emplace(T v) {
        if (Count == 0) {
            Head = Tail = new Elem<T>;
            Head->next = NULL;
        }
        else {
            Tail->next = new Elem<T>;
            Tail = Tail->next;
            Tail->next = NULL;
        }
        Tail->value = v;
        Count++;
    }

    void swap(Queue<T>* v) {
        std::swap(Head, v->Head);
        std::swap(Tail, v->Tail);
    }

    T back() {
        return Tail->value;
    }

    T front() {
        return Head->value;
    }

    bool empty()
    {
        return Head == NULL;
    }
};
#endif // QUEUE_H
