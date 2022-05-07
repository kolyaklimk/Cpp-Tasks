/*  Создать двухсвязанный список из случайных целых чисел.
 * Удалить из списка все элементы,
 * находящиеся между максимальным и минимальным.
*/
#ifndef TASK_H
#define TASK_H
#include "MyQueue.h"

template <class T>
class task : public MyQueue<T>
{
public:
    T min(){
        T buf = MyQueue<T>::front();
        for(int a=0;a<MyQueue<T>::size();a++){
            if(buf>MyQueue<T>::front()) buf = MyQueue<T>::front();
            MyQueue<T>::push(MyQueue<T>::front());
            MyQueue<T>::pop();
        }
        return buf;
    }

    T max(){
        T buf = MyQueue<T>::front();
        for(int a=0;a<MyQueue<T>::size();a++){
            if(buf<MyQueue<T>::front()) buf = MyQueue<T>::front();
            MyQueue<T>::push(MyQueue<T>::front());
            MyQueue<T>::pop();
        }
        return buf;
    }

    void del(){
        T buf1 = max();
        T buf2 = min();
        short q=0;
        for(int a=MyQueue<T>::size();a>0;a--){
            if(buf1== MyQueue<T>::front() || buf2 == MyQueue<T>::front()){
                q++;
                MyQueue<T>::push(MyQueue<T>::front());
                MyQueue<T>::pop();
                continue;
            }
            if(q>0 && q<2) MyQueue<T>::pop();
            else {
                MyQueue<T>::push(MyQueue<T>::front());
                MyQueue<T>::pop();
            }
        }
    }
};

#endif // TASK_H
