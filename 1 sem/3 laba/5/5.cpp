//Лабораторная 3, задача 5. Выполнена: Климкович Н. В.

/*Необходимо разложить функцию Y(x) из своего варианта в ряд
S(x), затем с помощью полученного ряда найти значение функции и сравнить его
со значением, вычисленным с помощью стандартных функций. Программа
должна запросить у пользователя количество членов ряда (n), затем запросить у
пользователя количество чисел, от которых он хочет посчитать функцию, затем
пользователь вводит по одному числу (x от 0.1, до 1), программа считает значение
функции с помощью ряда и с помощью стандартных функций и выводит оба
значения. Использование <cmath> запрещено.*/

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    double e, e1, e2, F, n, q1_, x, a, n1, n2, num;
    cout << "S(x)=((2x)^n)/(n!), Y(x)=e^2x.\n"
        << "\nThe number of members of the series n = ";
    cin >> n;
    n2 = n;
    while (n < 0 || n != int(n) || cin.fail()) {
        cout << "\nIncorrect value, n = ";
        cin >> n;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(9999, '\n');
        }
    }
    cout << "\nAmount of numbers: ";
    cin >> a;
    while (a <= 0 || a != int(a) || cin.fail()) {
        cout << "\nIncorrect value, a = ";
        cin >> a;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(9999, '\n');
            cin >> a;
        }
    }
    num = 0;
    for (int a1 = 1; a1 <= a; a1++) {
        n = n2;
        num++;
        cout << "\n\n0.1 <= x <= 1\nx" << num << " = ";
        cin >> x;
        while (x > 1 || x < 0.1 || cin.fail()) {
            cout << "Incorrect value, x" << num << " = ";
            cin >> x;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(9999, '\n');
                cin >> x;
            }
        }
        e = 1; n1 = 1;
        while (n1 <= n) {           //((2x)^n)/(n!)
                F = 1;
                q1_ = 1;
                for (double f1 = 1; f1 <= n1; f1++) F *= f1;
                for (int q11 = 1; q11 <= n1; q11++) q1_ *= 2 * x;
                e += q1_ / F;
                n1++;
        }
        e2 = 1; e1 = 2;
        n = 1;
        num = 0;
        while (e1 != e2) {          //e^2x
            e1 = e2;
            F = 1;
            q1_ = 1;
            for (double f1 = 1; f1 <= n; f1++) F *= f1;
            for (int q11 = 1; q11 <= n; q11++) q1_ *= 2 * x;
            e2 += q1_ / F;
            n++;
        }
        if (n2 == 0) cout << "S(x" << num << ") = " << 1 << "\nY(x" << num << ") = " << e2;
        else cout << "S(x" << num << ") = " << e << "\nY(x" << num << ") = " << e2;
    }

    return 0;
}