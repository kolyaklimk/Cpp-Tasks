//Лабораторная 4, задача 5. Выполнена: Климкович Н. В.

/*сглаживание матрицы*/

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int t1, t, t2, N, M, q_, n, y, q, q1;
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
    N += 2;
    M += 2;
    q_ = 1;

    //двумерный массив 1
    double** a = new double* [N];
    for (q = 0; q < N; q++) {
        a[q] = new double[M];

        //ввод в MAX
        for (q1 = 0; q1 < M; q1++)
            a[q][q1] = INT_MAX;
    }

    //ввод значений в массив
    for (q = 1; q < N - 1; q++)
        for (q1 = 1; q1 < M - 1; q1++) {
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
            if (t2 < t) t2 = t+1;
        }

    //вывод таблицы 1
    cout << "\n\n";
    for (q = 1; q < N - 1; q++) {
        for (q1 = 1; q1 < M - 1; q1++) cout << setw(2*t2) << a[q][q1];
        cout << "\n";
    }

    cout << "\n\n";
    //сглаживание матрицы
    for (q = 1; q < N - 1; q++)
        for (q1 = 1; q1 < M - 1; q1++) {
            n = 4;
            y = a[q][q1];
            if (a[q][q1 - 1] == INT_MAX) {
                n--;
                a[q][q1 - 1] = 0;
            }
            if (a[q + 1][q1] == INT_MAX) {
                n--;
                a[q + 1][q1] = 0;
            }
            if (a[q - 1][q1] == INT_MAX) {
                n--;
                a[q - 1][q1] = 0;
            }
            if (a[q][q1 + 1] == INT_MAX) {
                n--;
                a[q][q1 + 1] = 0;
            }
            a[q][q1] = (a[q][q1 + 1] + a[q][q1 - 1] + a[q + 1][q1] + a[q - 1][q1]) / n;

            //вывод таблы 2
            if (q != q_) cout << "\n";
            cout << setw(2*t2) << a[q][q1];
            q_ = q;
            a[q][q1] = y;
        }

    for (q = 0; q < N; q++)
        delete [] a[q];
    delete[] a;
}