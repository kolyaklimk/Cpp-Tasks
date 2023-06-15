//Лабораторная 4, задача 4. Выполнена: Климкович Н. В.

/*посчитать количество локальных минимумов матрицы*/

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int t1, t, t2, N, M, min, q_, q1_, min1, q, q1;
    cout << "NxM:\n N = ";
    cin >> N;
    cout << "M = ";
    cin >> M;
    while (N < 2 || M < 2 || cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "\nIncorrect value, N = ";
            cin >> N;
            cout << "M = ";
            cin >> M;
    }
    t2 = 1;
    min1 = 0;
    N += 2;
    M += 2;

    //двумерный массив
    int** a = new int* [N];
    for (q = 0; q < N; q++) {
        a[q] = new int[M];

        //ввод MAX
        for (q1 = 0; q1 < M; q1++)
            a[q][q1] = INT_MAX;
    }

    //ввод значений в массив
    for (q = 1; q < N-1; q++)
        for (q1 = 1; q1 < M-1; q1++) {
            cout << "N" << q << ", " << "M" << q1 << " = ";
            cin >> a[q][q1];
            while (a[q][q1] > INT_MAX - 2 || cin.fail()) {
                cin.clear();
                cin.ignore(9999, '\n');
                cout << "N" << q << ", " << "M" << q1 << " = ";
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
    
    //количество локальных минимумов
    for (q = 1; q < N-1; q++)
        for (q1 = 1; q1 < M - 1; q1++) {
            q_ = q;
            q1_ = q1;
            if (a[q_][q1_] < a[q_ - 1][q1_] && a[q_][q1_] < a[q_][q1_ + 1] && a[q_][q1_] < a[q_ + 1][q1_] && a[q_][q1_] < a[q_][q1_ - 1]) min1++;
        }
    
    //вывод таблицы
    cout << "\n\n";
    for (q = 1; q < N-1; q++) {
        for (q1 = 1; q1 < M-1; q1++) cout << setw(t2) << a[q][q1] << " ";
        cout << "\n";
    }

    cout << "min = " << min1;

    for (q = 0; q < N; q++)
        delete[] a[q];
    delete[] a;
}