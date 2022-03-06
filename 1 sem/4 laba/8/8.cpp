//Лабораторная 4, задача 8. Выполнена: Климкович Н. В.

/*Заменить нулями все элементы, которые находятся в ячейках
между минимальным и максимальным элементами (не включая их).
Изначально все элементы в массиве различные. Если после данного действия
большая часть массива будет содержать нули, то удалить все нулевые
элементы из массива (c сохранением порядка следования остальных
элементов).*/

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int k, min, max, q, q_, q1_, t, null, k1;
    cout << "K = ";
    cin >> k;
    while (k <2 || cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "\nIncorrect value, k = ";
            cin >> k;
    }
    q_ = 0;
    q1_ = 0;
    t = 1;
    null = 0;
    k1 = 0;
    int* a = new int[k];
    while (t != 2) {
        t = 0;
        //ввод значений в массив
        for (q = 0; q < k; q++) {
            cout << "K" << q + 1 << " = ";
            cin >> a[q];
            while (cin.fail()) {
                cin.clear();
                cin.ignore(9999, '\n');
                cout << "K" << q + 1 << " = ";
                cin >> a[q];
            }
        }

        //поиск минимального 
        min = a[0];
        for (q = 0; q < k; q++)
            if (min >= a[q]) {
                min = a[q];
                q_ = q;
            }

        //поиск максимального 
        max = a[0];
        for (q = 0; q <= k; q++)
            if (max <= a[q]) {
                max = a[q];
                q1_ = q;
            }

        //проверка на неcколько значений минимального
        for (q = 0; q <= k; q++)
            if (min == a[q]) t++;

        //проверка на неcколько значений максимального
        for (q = 0; q <= k; q++)
            if (max == a[q]) t++;

        if (t != 2) cout << "several min or max, repeat\n\n";
    }
    cout << min << " " << max<< "\n";

    if (abs(q_ - q1_) != 1) {
        //минимальное первое
        if (q_ < q1_) {
            for (q = q_ + 1; q < q1_; q++) {
                a[q] = 0;
                null++;
            }
            if (null > k / 2) {
                for (q = q_ + 1; q < q1_; q++) {
                    a[q] = a[q + q1_ - q_-1];
                    k1 = (q1_ - q_-1);
                }
            }
        }
        //максимальное первое
        else {
            for (q = q1_ + 1; q < q_; q++) {
                a[q] = 0;
                null++;
            }
            if (null > k / 2) {
                for (q = q1_ + 1; q < q_; q++) {
                    a[q] = a[q + q_ - q1_-1];
                    k1 = (q_ - q1_-1);
                }
            }

        }
    }

    //вывод
    for (q = 0; q < k - k1; q++) {
        cout << a[q] << " ";
    }

    delete[] a;
}