#ifndef TABLE_H
#define TABLE_H
#include <QTextBrowser>
#include <QDebug>
#include <QtMath>
struct Elem{
    int item=1e7;
    Elem* next=nullptr;
};

class table
{
private:
    int size = 256;
    int Count_m=0;
    int Count =0;
    Elem* arr=nullptr;

    int hashKey(const int& v){
        if(v<0) return (int(qFabs(v))+31)%(size-1);
        return v%(size-1);
    }

    void clearDel(){
        for(int a=0;a<size;a++){
            while(arr[a].next!=nullptr){
                Elem* buf=&arr[a];
                while(buf->next->next!=nullptr){
                    buf=buf->next;
                }
                delete buf->next;
                buf->next=nullptr;
            }
        }
        delete arr;
        Count_m=0;
        Count =0;
    }
public:
    void clear(){
        for(int a=0;a<size;a++){
            while(arr[a].next!=nullptr){
                Elem* buf=&arr[a];
                while(buf->next->next!=nullptr){
                    buf=buf->next;
                }
                delete buf->next;
                buf->next=nullptr;
            }
            arr[a].item=1e7;
        }
        Count_m=0;
        Count =0;
    }
    table(int s=1024){
        size=s;
        arr=new Elem[size];
    }
    ~table(){
        clearDel();
    }

    bool empty(){
        return !Count;
    }
    void push(const int& v){
        if(Count_m<size-1){
            int key=hashKey(v);
            if(arr[key].item==1e7){
                Count_m++;
                arr[key].item=v;
            }
            else {
                Elem* buf=&arr[key];
                while(buf->next!=nullptr) buf=buf->next;
                buf->next=new Elem;
                buf->next->item=v;
            }
            Count++;
        }
        else
        {
        resize();
        push(v);
        }
    }
    void erase(int v){
        int key=hashKey(v);
        //qDebug() << "----------";
        if(key>=0 && key<size){
            if(arr[key].next==nullptr){
                if(v==arr[key].item){
                    Count_m--;
                    arr[key].item=1e7;
                    Count--;
                }
            }
            else {
                Elem* buf=&arr[key];
                while(buf->next!=nullptr){
                if(buf->next->item==v){
                    Elem* del=buf->next;
                    buf->next=buf->next->next;
                    delete del;
                    Count--;
                    break;
                    }
                buf=buf->next;
                }
            }
        }
    }

    void resize(){
        table* newTable = new table(size*2);
        for(int a=0;a<size;a++){
            if(arr[a].next!=nullptr){
                Elem* buf=arr[a].next;
                while(buf!=nullptr){
                    newTable->push(buf->item);
                    buf=buf->next;
                }
            }
            newTable->push(arr[a].item);
        }
        clearDel();
        arr=newTable->arr;
        Count=newTable->Count;
        Count_m=newTable->Count_m;
        size=newTable->size;
    };
    int count(){
        return Count;
    }
    int Size(){
        return size;
    }

    QString at(const int& v){
        int key=hashKey(v);
        if(key>=0 && key<size){
            if(v==arr[key].item){
                return "Hash of " + QString::number(arr[key].item) +
                        ": " + QString::number(hashKey(arr[key].item));
                }
            else
            {
                Elem* buf=&arr[key];
                while(buf->next!=nullptr){
                if(buf->next->item==v){
                    return "Hash of " + QString::number(buf->next->item) +
                            ": " + QString::number(hashKey(buf->next->item));
                    break;
                    }
                buf=buf->next;
                }
            }
        }
        return "error";
    }

    void print(QTextBrowser* t){
        t->clear();
        for(int a=0;a<size;a++){
            if(arr[a].next!=nullptr){
                Elem* buf=&arr[a];
                while(buf!=nullptr){
                    if(buf->item!=1e7)
                    t->append("Hash of " + QString::number(buf->item) +
                              ": " + QString::number(hashKey(buf->item)));
                    buf=buf->next;
                }
            }
            else{
            if(arr[a].item!=1e7)
            t->append("Hash of " + QString::number(arr[a].item) +
                      ": " + QString::number(hashKey(arr[a].item)));
            }
        }
    }
};

#endif // TABLE_H
