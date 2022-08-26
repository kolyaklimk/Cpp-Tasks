//Лабораторная 2, задача 6. Выполнена: Климкович Н. В.

//Составить программу используя переключатель switch.

#include <iostream>
using namespace std;
int main()
{
    double a, b, c;
    int n;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;
    cout << "N = "; cin >> n;

    switch (n) {
    case 2: cout << b * c - a * a; break;
    case 56: cout << b * c; break;

    case 7: cout << a * a + c; break;
    case 3: cout << a - b * c; break;
    default: cout << pow((a + b), 3);
    }
}