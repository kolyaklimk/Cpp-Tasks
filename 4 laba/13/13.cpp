//Лабораторная 4, задача 13. Выполнена: Климкович Н. В.

/*У Миши в общежитии всего лишь 1 розетка. Дабы исправить это
недоразумение, Миша купил N удлинителей таких, что i-й удлинитель имеет
a[i] входов. Вычислите, сколько розеток получится у Миши, если он
оптимально соединит удлинители?*/

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int n, q, m, sum;
    cout << "N = ";
    cin >> n;
    while (n < 0 || cin.fail()) {
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "\nIncorrect value, N = ";
        cin >> n;
    }

    int* a = new int[n];

    //ввод значений в массив + сколько всего разеток
    m = 1;
    sum = 0;
    for (q = 0; q < n; q++) {
        a[q] = m;
        m++;
        sum += a[q];
    }
    sum -= n-1;

    //вывод
    cout << "\n" << sum;

    delete[] a;
}