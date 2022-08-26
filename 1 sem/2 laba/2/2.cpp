//Лабораторная 2, задача 2. Выполнена: Климкович Н. В.

/*Меньшее из двух значений переменных целого типа Х и Y заменить
нулём, а в случае их равенства - заменить нулями оба; наибольшее из трёх
различных значений переменных вещественного типа А, В и С уменьшите на K.
K вводится с клавиатуры.*/

#include <iostream>
using namespace std;
int main()
{
    int x, y;
    cout << "x = "; cin >> x;
    cout << "y = "; cin >> y;

    if (x > y) {
        y = 0;
        cout << "x > y, so y = " << y << "\n";
    }

    else if (x < y) {
        x = 0;
        cout << "x < y, so x = " << x << "\n";
    }

    if (x == y) {
        x = 0;
        y = 0;
        cout << "x == y, so x = " << x << " and y = " << y << "\n";
    }

    /////////////////////////

    cout << "\n////////////////\n\n";

    double a, b, c, k;
        cout << "A = "; cin >> a;
        cout << "B = "; cin >> b;
        cout << "C = "; cin >> c;
        cout << "K = "; cin >> k;
        
    if (a == b && b == c)
        cout << "A == B == C";

    if (a > b && a > c) {
        a = a - k;
        cout << "\nA - K = " << a;
    }

    if (b > c && b > a) {
        b = b - k;
        cout << "\nB - K = " << b;
    }

    if (c > b && c > a) {
        c = c - k;
        cout << "\nC - K = " << c;
    }

    return 0;
}