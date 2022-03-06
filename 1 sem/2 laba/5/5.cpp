//Лабораторная 2, задача 5. Выполнена: Климкович Н. В.

//Составить программу используя условный оператор if.

#include <iostream>
using namespace std;
int main()
{
    double a, b, c, d;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;
    cout << "d = "; cin >> d;

    if (c >= d && a < d)
        cout << "Z = " << a + b / c;

    else if (c < d && a >= d)
        cout << "Z = " << a - b / c;

    else cout << "Z = 0";

    return 0;
}
