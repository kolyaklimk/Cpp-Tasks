//Лабораторная 4, задача 14. Выполнена: Климкович Н. В.

/*На вход подаётся поле для игры в "сапёр" размером n*m
символов, где символ '.' означает пустое место, а символ '*' - бомбу.
Требуется дополнить это поле числами , как в оригинальной игре. Выделение
памяти через функции языка С.*/

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int n, m, q, q1, s1, q_, q1_, z;
    char s;
    cout << "n = ";
    cin >> n;
    cout << "m = ";
    cin >> m;
    while (n < 2|| m < 2 || cin.fail()) {
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "\nIncorrect value, n = ";
        cin >> n;
        cout << "m = ";
        cin >> m;
    }
    m += 2;
    n += 2;

    //двумерный массив
    int** a = (int**)malloc(n * sizeof(int*));
    for (q = 0; q < n; q++)
        a[q] = (int*)malloc(m * sizeof(int));

    //ввод 0 в массив
    for (q = 0; q < n; q++)
        for (q1 = 0; q1 < m ; q1++) {
            a[q][q1] = 0;
        }

    //ввод улсовие в массив
    for (q = 1; q < n-1; q++)
        for (q1 = 1; q1 < m-1; q1++) {
            cout << "[" << q << "][" << q1 << "] = ";
            cin >> s;
            while ((s != '.' && s != '*') || cin.fail()) {
                cin.clear();
                cin.ignore(9999, '\n');
                cout << "[" << q << "][" << q1 << "] = ";
                cin >> s;
            }
            if (s == '.') s1 = 0;
            else s1 = 9;
            a[q][q1] =s1;
        }

    //ввод результат в массив
    for (q = 1; q < n - 1; q++)
        for (q1 = 1; q1 < m - 1; q1++) {
            z = 0;
            if (a[q][q1] == 0) {
                for (q_ = q - 1; q_ < q + 2; q_++)
                    for (q1_ = q1 - 1; q1_ < q1 + 2; q1_++)
                        if (a[q_][q1_] == 9)
                            a[q][q1]++;
            }
        }
    
    //вывод таблицы 1
    cout << "\n\n";
    for (q = 1; q < n-1; q++) {
        for (q1 = 1; q1 < m-1; q1++) {
            if (a[q][q1] == 0)
                cout << setw(3) << ".";
            else if (a[q][q1] == 9)
                cout << setw(3) << "*";
            else cout << setw(3) << a[q][q1];
        }
        cout << "\n";
    }

    for (q = 0; q < n; q++)
        free(a[q]);
    free(a);
}