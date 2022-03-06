//Лабораторная 5, задача Доп_2. Выполнена: Климкович Н. В.

/*Рекурсивная функция задана следующим образом:
Вычислить значение.

Входные данные:
Каждая строка содержит три целых числа: k (0 < k < 10^19), n (0 < n < 10^19) и t (0 < t < 10).
Последняя строка содержит три нуля и не обрабатывается.

Выходные данные:
Для каждого теста в отдельной строке вывести номер теста и значение x. Формат вывода
приведен в примере.*/

#include <iostream>
using namespace std;

unsigned long long rec(unsigned long long k, unsigned long long n, unsigned long long m)
{
	if (n == 0) return 1;
	if (n & 1) return (k * rec((k * k) % m, n / 2, m)) % m;
	return rec((k * k) % m, n / 2, m);
}

int main()
{
    unsigned long long k, n, t, x, m, w = 0;
    int* a = (int*)malloc(w * sizeof(int));
    for (;;) {
        m = 1;
        a = (int*)realloc(a, ++w * sizeof(int));
        cin >> k;
        cin >> n;
        cin >> t;
        if (k == 0 && n == 0 && t == 0) {
            cout << "\n";
            for (int i = 0; i < w - 1; i++)
                cout << "Case #" << i + 1 << ": " << a[i] << "\n";
            return 0;
        }
        while (cin.fail() || k < 1 || n < 1 || t < 1 || t > 10) {
            cin.clear();
            cin.ignore(9999, '\n');
            cout << "\nIncorrect value\n";
            cin >> k;
            cin >> n;
            cin >> t;
        }
        for (int i = 0; i < t; i++) m *= 10;
        a[w - 1] = rec(k % m, n, m);
    }
}