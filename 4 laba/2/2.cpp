//Лабораторная 4, задача 2. Выполнена: Климкович Н. В.

/*найти минимальный среди элеметов выше главной оси*/

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int t1, t, t2, N, M, min, q1, q11, q;
    double k;
    cout << "NxM:\n N = ";
    cin >> N;
    cout << "M = ";
    cin >> M;
    while (M >=99 || N >=99 || N < 2 || M < 2 || cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "\nIncorrect value, N = ";
            cin >> N;
            cout << "M = ";
            cin >> M;
    }
    t2 = 1;

    int a[99][99];

    //ввод значений в массив
    for (q = 0; q < N; q++) 
        for (q1 = 0; q1 < M; q1++) {
            cout << "N" << q + 1 << ", " << "M" << q1 + 1 << " = ";
            cin >> a[q][q1];
            while (a[q][q1] > INT_MAX - 2 || cin.fail()) {
                cin.clear();
                cin.ignore(9999, '\n');
                cout << "N" << q + 1 << ", " << "M" << q1 + 1 << " = ";
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
        for (q1 = 0; q1 < M; q1++) cout << setw(t2) << a[q][q1] << " ";
        cout << "\n";
    }

    //минимальное значение выше главной оси
    cout << "\n\n";
    min = INT_MAX;
    for (q = 0; q < N; q++) {
        if (N == M) k = 0;
        else k = trunc(M / N);

        for (q1 = 0; q1 < M; q1++) {
            if (q * M < q1 * N) {
                if (q + 1 == N && q1 + 1 == M) break;
                else {
                    q11 = q1;
                    if (q1 + k + 1 <= M) q1 += k;
                    if (min > a[q][q1]) min = a[q][q1];
                    a[q][q1] = 0;
                    if (q11 < q1) q1 -= k;
                }
            }
        }
    }
    cout << min;


    //вывод таблицы
    cout << "\n\n";
    for (q = 0; q < N; q++) {
        for (q1 = 0; q1 < M; q1++) cout << setw(t2) << a[q][q1] << " ";
        cout << "\n";
    }
}