//Лабораторная 4, задача 11. Выполнена: Климкович Н. В.

/*Дан трёхмерный динамический массив размером n^3 целых
неотрицательных чисел. Необходимо определить диагональ с наибольшей
суммой чисел. Для обхода диагоналей нельзя использовать вложенные
циклы.*/

#include <iostream>
using namespace std;
int main()
{
    int N, q, q1, q2, d1, d2, d3, d4, max_;
    cout << "NxNxN:\n N = ";
    cin >> N;
    while (N < 2 || cin.fail()) {
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "\nIncorrect value, N = ";
        cin >> N;
    }

    //3-й массив
    int*** a = new int** [N];
    for (q = 0; q < N; q++) {
        a[q] = new int* [N];
        for (q1 = 0; q1 < N; q1++)
            a[q][q1] = new int[N];
    }

    //ввод значений в массив
    for (q = 0; q < N; q++)
        for (q1 = 0; q1 < N; q1++)
            for (q2 = 0; q2 < N; q2++) {
                cout << "N[" << q + 1 << "][" << q1 + 1 << "][" << q2 + 1 << "] = ";
                cin >> a[q][q1][q2];
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(9999, '\n');
                    cout << "N[" << q + 1 << "][" << q1 + 1 << "][" << q2 + 1 << "] = ";
                    cin >> a[q][q1][q2];
                }
            }

    //поиск диагоналей
    d1 = 0; 
    d2 = 0;
    d3 = 0;
    d4 = 0;

    //от [1][1][1] до [N][N][N] (права верх - лево низ)
    for (q = 0, q1 = 0, q2 = 0; q < N && q1 < N && q2 < N; q++, q1++, q2++)
        d1 += a[q][q1][q2];
    //от [1][N][1] до [N][1][N] (лево верх - право низ)
    for (q = 0, q1 = N - 1, q2 = 0; q < N && q1 >= 0 && q2 < N; q++, q1--, q2++)
        d2 += a[q][q1][q2];
    //от [N][1][1] до [1][N][N] (лево низ - право верх)
    for (q = N-1, q1 = 0, q2 = 0; q >=0 && q1 < N && q2<N; q--, q1++, q2++)
        d3 += a[q][q1][q2];
    //от [N][N][1] до [1][1][N] (право низ - лево верх)
    for (q = N - 1, q1 = N - 1, q2 = 0; q >= 0 && q1 >= 0 && q2 < N; q--, q1--, q2++)
        d4 += a[q][q1][q2];

    max_ = max(max(d1, d2), (d3, d4));

    if (max_ == d1) cout << "\nMax diagonal from [1][1][1] to [N][N][N] = " << d1;
    if (max_ == d2) cout << "\nMax diagonal from [1][N][1] to [N][1][N] = " << d2;
    if (max_ == d3) cout << "\nMax diagonal from [N][1][1] to [1][N][N] = " << d3;
    if (max_ == d4) cout << "\nMax diagonal from [N][N][1] to [1][1][N] = " << d4;


    for (q = 0; q < N; q++) 
        for (q1 = 0; q1 < N; q1++)
            delete[] a[q][q1];

    for (q = 0; q < N; q++)
            delete[] a[q];

    delete[] a;
}