//Лабораторная 2, задача 3. Выполнена: Климкович Н. В.

/*Написать программу нахождения максимального из двух
вещественных чисел X и Y с использованием тернарной операции. Написать
два варианта программы. С использованием переменной логического типа для
определения условия и без неё.*/

#include <iostream>
using namespace std;
int main()
{
    double x, y;
    bool t;
    cout << "x = "; cin >> x;
    cout << "y = "; cin >> y;

    cout << "1 option: ";
    (x > y) ? cout << "x is max" : (x == y) ? cout << "x == y" : cout << "y is max";
    
    cout << "\n2 option: ";
    t = (x > y) ? 1 : (x == y) ? 1 : 0;
    (t == 1) ? (x > y) ? cout << "x is max" : cout << "x == y" : cout << "y is max";
    return 0;
}