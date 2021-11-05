//Лабораторная 4, задача 3. Выполнена: Климкович Н. В.

/*является ли матрица ортонормированной*/

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int t1, t, t2, N, k, q, q1;
    cout << "NxN:\n N = ";
    cin >> N;
    t2 = 1;
    while ( N<2 || cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "\nIncorrect value, N = ";
            cin >> N;
    }

    //двумерный массив
    int** a = new int* [N];
    for (q = 0; q < N; q++) {
        a[q] = new int[N];
    }

    //ввод значений в массив
    for (q = 0; q < N; q++)
        for (q1 = 0; q1 < N; q1++) {
            cout << "N[" << q + 1 << "][" << q1 + 1 << "]" << " = ";
            cin >> a[q][q1];
            while (cin.fail()) {
                cin.clear();
                cin.ignore(9999, '\n');
                cout << "N[" << q + 1 << "][" << q1 + 1 << "]" << " = ";
                cin >> a[q][q1];
            }
            t1 = a[q][q1];
            t = 2;
            while (t1 > 10) {
                t1 /= 10;
                t++;
            }
            if (t2 < t) t2 = t;
        }
    
    //вывод таблицы
    cout << "\n\n";
    for (q = 0; q < N; q++) {
        for (q1 = 0; q1 < N; q1++) cout << setw(t2) << a[q][q1] << " ";
        cout << "\n";
    }
    cout << "\n\n";

    //скалярное произведение различных пар строк
    for (q = 0; q < N; q++)
        for (q1 = 0; q1 < N; q1++) {
            if (q1 == N - 1 || q == N - 1) break;
            else {
                if (a[q][q1] * a[q + 1][q1] == 0) continue;
                else {
                    cout << "Matrix not Orthonormal";
                    return 0;
                }
            }
        }
    
    //скалярное произведение каждой строки
    for (q = 0; q < N; q++) {
        k = 0;
        for (q1 = 0; q1 < N; q1++) k += a[q][q1];
        if (k == 1) continue;
        else {
            cout << "Matrix not Orthonormal";
            return 0;
        }
    }
    cout << "Matrix Orthonormal";

    for (q = 0; q < N; q++) {
        delete[] a[q];
    }
    delete[] a;
}