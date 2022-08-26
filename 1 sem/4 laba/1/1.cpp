//Лабораторная 4, задача 1. Выполнена: Климкович Н. В.

/*удалить min и max элементы массива*/

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int t, t1, t2, min, min1, max, max1, q1, q2, k1, k2, k, r, q;
    cout << "k = ";
    cin >> k;
    while (k < 2 || k >=9999 || cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "\nIncorrect value, k = ";
            cin >> k;
    }
    r = 1;
    t2 = 1;
    q1 = 0; 
    q2 = 0;
    k1 = k;

    int a[9999];

    //построение таблицы
    for (q = 0; q < k; q++) {
        cout << "k" << q + 1 << " = ";
        cin >> a[q];
        while (cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "k" << q + 1 << " = ";
            cin >> a[q];
        }
        t1 = a[q];
        t = 2;
        while (t1 > 10) {
            t1 /= 10;
            t++;
        }
        if (t2 < t) t2 = t;
    }

    //вывод таблицы
    cout << "\n\n";
    for (q = 0; q < k; q++) {
        cout << setw(t2) << a[q];
        if ((q + 1) / r == 5) {
            r += 1;
            if (q == k-1) cout << "\n";
            else cout << " -->\n";
        }
    }

    //минимальное значение
    min = a[0];
    for (q = 0; q < k; q++) {
        if (min >= a[q]) {
            min = a[q];
            min1 = q;
        }
    }
    
    //кол-во минимальных
    for (q = 0; q < k; q++) {
        if (a[q] == min) q1++;
    }

    //удаление минимального значения
    for (q = 0; q < k; q++) {
        if (min == a[q]) {
            min1 = q;
            for (q = min1; q < k1; q++) a[q] = a[q + 1];
            k1--;
        }
    }

    k2 = k-q1;
    //максимальное значение
    max = a[0];
    for (q = 0; q < k-q1; q++) {
        if (max <= a[q]) {
            max = a[q];
            max1 = q;
        }
    }

    //кол-во максимальных
    for (q = 0; q < k-q1; q++) {
        if (a[q] == max) q2++;
    }

    //удаление максимального значения
    for (q = 0; q < k-q1; q++) {
        if (max == a[q]) {
            max1 = q;
            for (q = max1; q < k2; q++) a[q] = a[q + 1];
            k2--;
        }
    }

    cout << "\n\nmin = " << min
        << "\nmax = " << max << "\n";
}