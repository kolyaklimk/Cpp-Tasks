//Лабораторная 1, задача 6. Выполнена: Климкович Н. В.

/*Студент начал решать задачи данного урока программирования,
когда электронные часы показывали h1 часов и min1 минут, а закончил, когда
было h2 часов и min2 минут. Составьте программу, позволяющую определить,
сколько времени студент решал эти задачи. (Будем считать, что задачи
решались не дольше суток).*/

#include <iostream>
using namespace std;
int main()
{
    int h1, h2, min1, min2;

    cout << "start time:" << endl << "h1 = ";
    cin >> h1;
    cout << "min1 = ";
    cin >> min1;

    cout << endl << "completion time:" << endl << "h2 = ";
    cin >> h2;
    cout << "min2 = ";
    cin >> min2;

    int m1 = h1 * 60 + min1;
    int m2 = h2 * 60 + min2;

    cout << endl << "working hours:";

    if (m2 > m1) {
        int m_ = m2 - m1;
        cout << endl << "h = " << m_ / 60 << endl << "min = " << m_ % 60;
    }
    else {
        int m_2 = 1440 - (m1 - m2);
        cout << endl << "h = " << m_2 / 60 << endl << "min = " << m_2 % 60;
    }
    return 0;
}