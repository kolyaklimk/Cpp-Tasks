//Лабораторная 2, задача 1. Выполнена: Климкович Н. В.

/*Заданы два целых числа x и y. Определите, верно ли, что одно из них
делится на другое без остатка, или нет.*/

#include <iostream>
using namespace std;
int main()
{
    int x, y;
    cout << "x = "; cin >> x;
    cout << "y = "; cin >> y;

    if (x % y == 0)
        cout << "x/y without remainder\n";
    else cout << "x/y with remainder\n";

    if (y % x == 0)
        cout << "y/x without remainder";
    else cout << "y/x with remainder";

    return 0;
}