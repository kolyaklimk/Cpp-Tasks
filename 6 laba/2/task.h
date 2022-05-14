#ifndef TASK_H
#define TASK_H

#include "table.h"

class task: public table
{
public:
    task(){};
    void deleteMinus(){
        for(int q=0;q<Size();q++)
        for(int a=-1;a>-11;a--) erase(a);
    }
};

#endif // TASK_H
