//Лабораторная 4, задача 7. Выполнена: Климкович Н. В.

/*Дано натуральное число n. Требуется подсчитать количество цифр
числа и определить, какая цифра стоит в разряде с номером i (разряды
нумеруются с конца, т.е. разряд единиц имеет номер 0).*/

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int n, i, q, w, q1, u;
    cout << "N = ";
    cin >> n;
    while (n<1|| cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "\nIncorrect value, n = ";
            cin >> n;
    }
    q1 = n;

    //количество цифр
    for (u = 10, w = 0, q = 1; q >= 1; u *= 10) {
        q = n / u;
        w++;
    }

    cout << "i = ";
    cin >> i;
    while (i < 0 || i >= w || cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "\nIncorrect value, i = ";
            cin >> i;
    }
    //внесение в массив
    int *a = new int[w];
    for (u = 10, w = 0, q = 1; q >= 1; u *= 10) {
        q = n / u;
        a[w] = q1 - q * 10;
        w++;
        q1 = q;
    }

    cout << "\nNumber of digits: " << w
        << "\nDigit in place - " << i << ": " << a[i];

    delete[] a;
}