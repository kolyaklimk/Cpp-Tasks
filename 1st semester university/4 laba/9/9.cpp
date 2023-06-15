//Лабораторная 4, задача 9. Выполнена: Климкович Н. В.

/*В качестве входных данных поступают две целочисленные
матрицы A и B, которые имеют размер N и соответственно. Требуется найти
произведение матриц A*B. Выделение памяти через функции языка С.*/

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int n, q, q1, t1, t, t2, t3, q_,k;
    cout << "N = ";
    cin >> n;
    while (n < 2 || cin.fail()) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "\nIncorrect value, N = ";
            cin >> n;
    }
    t2 = 1;
    t3 = 1;
    q_ = 1;

    //двумерный массив 1
    int **a = (int**)malloc(n * sizeof(int*));
    for (q = 0; q < n; q++)
        a[q] = (int*)malloc(n * sizeof(int));

    //двумерный массив 2
    int** b = (int**)malloc(n * sizeof(int*));
    for (q = 0; q < n; q++)
        b[q] = (int*)malloc(n * sizeof(int));

    //двумерный массив 3
    int** c = (int**)malloc(n * sizeof(int*));
    for (q = 0; q < n; q++)
        c[q] = (int*)malloc(n * sizeof(int));

    //ввод значений в массив 1
    for (q = 0; q < n; q++)
        for (q1 = 0; q1 < n; q1++) {
            cout << "A[" << q << "][" << q1  << "] = ";
            cin >> a[q][q1];
            while (n < 2 || cin.fail()) {
                cin.clear();
                cin.ignore(9999, '\n');
                cout << "A[" << q << "][" << q1 << "] = ";
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

    //ввод значений в массив 2
    for (q = 0; q < n; q++)
        for (q1 = 0; q1 < n; q1++) {
            cout << "B[" << q << "][" << q1 << "] = ";
            cin >> b[q][q1];
            while (n < 2 || cin.fail()) {
                cin.clear();
                cin.ignore(9999, '\n');
                cout << "B[" << q << "][" << q1 << "] = ";
                cin >> b[q][q1];
            }
            t1 = b[q][q1];
            t = 2;
            while (t1 > 10) {
                t1 /= 10;
                t++;
            }
            if (t3 < t) t3 = t;
        }

    //ввод 0 значений в массив 3
    for (q = 0; q < n; q++)
        for (q1 = 0; q1 < n; q1++) {
            c[q][q1] = 0;
        }

    //вывод таблицы 1
    cout << "\n\n";
    for (q = 0; q < n; q++) {
        for (q1 = 0; q1 < n; q1++) cout << setw(t2) << a[q][q1] << " ";
        cout << "\n";
    }

    //вывод таблицы 2
    cout << "\n\n";
    for (q = 0; q < n; q++) {
        for (q1 = 0; q1 < n; q1++) cout << setw(t3) << b[q][q1] << " ";
        cout << "\n";
    }

    //умножение матриц A*B
    for (q = 0; q < n; q++) {
        for (q1 = 0; q1 < n; q1++) {
            for (k = 0; k < n; k++)
                c[q][q1] += a[q][k] * b[k][q1];

            t1 = c[q][q1];
            t = 2;
            while (t1 > 10) {
                t1 /= 10;
                t++;
            }
            if (t2 < t) t2 = t;
        }
    }

    //вывод таблицы 3
    cout << "\n\n";
    for (q = 0; q < n; q++) {
        for (q1 = 0; q1 < n; q1++) cout << setw(t2) << c[q][q1] << " ";
        cout << "\n";
    }

    for (q = 0; q < n; q++)
        free(a[q]);
    free(a);

    for (q = 0; q < n; q++)
        free(b[q]);
    free(b);

    for (q = 0; q < n; q++)
        free(c[q]);
    free(c);


}