//Лабораторная 4, задача 12. Выполнена: Климкович Н. В.

/*Написать функцию которая будет удалять дубликаты элементов
из массива. Входные параметры: массив, длинна массива. Выходные
параметры: новый массив, новый размер.*/

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int k, q, t, s,q1,q_,k1;
    cout << "K = ";
    cin >> k;
    while (k < 2 || cin.fail()) {
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "\nIncorrect value, k = ";
        cin >> k;
    }
    k += 1;
    k1 = 0;
    int* a = new int[k];

    //ввод значений в массив
    for (q = 0; q < k-1; q++) {
        cout << "K" << q + 1 << " = ";
        cin >> a[q];
        while (cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "K" << q + 1 << " = ";
            cin >> a[q];
        }
    }

    //поиск и удаление дубликатов
    for (q = 0; q < k-1-k1; q++) {
        t = 0;
        s = a[q];
        while (t != 1) {
            t = 0;
            for (q1 = 0; q1 < k-1-k1; q1++)
                if (s == a[q1]) {
                    t++;
                    q_ = q1;
                }

            if (t != 1) {
                for (q1 = q_; q1 < k - 1 - k1; q1++)
                    a[q1] = a[q1 + 1];
                k1++;
            }
        }
    }


    int* b = new int[k-k1];

    for (q = 0; q < k - 1 - k1; q++)
        b[q] = a[q];

    //вывод
    cout << "\n\n";
    for (q = 0; q < k-k1-1; q++) {
        cout << b[q] << " ";
    }
    
    delete[] b;
    delete[] a;
}