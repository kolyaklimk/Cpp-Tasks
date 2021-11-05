﻿//Лабораторная 5, задача Доп_1. Выполнена: Климкович Н. В.

/*Определим следующую рекурсивную функцию F(n).
Определим функцию S (p, q) следующим образом.
По заданным p и q необходимо вычислить S (p, q).

Входные данные:
Состоит из нескольких тестов. Каждая строка содержит два неотрицательных целых числа p и
q (p ≤ q), разделенных пробелом. p и q являются 32 битовыми знаковыми целыми. Последняя
строка содержит два отрицательных целых числа и не обрабатывается.

Выходные данные:
Для каждой пары p и q в отдельной строке вывести значение S (p, q).*/

#include <iostream>
using namespace std;
/*
int rec(int p, int q)
{
	if (p == q + 1) return 0;
	if (p == 0) return 0 + rec(p + 1, q);
	if (p % 10 > 0) return  p % 10 + rec(p + 1, q);
	return p / 10 + rec(p + 1, q);
}

int main()
{
	int p, q;
	cin >> p;
	cin >> q;
	while (cin.fail() || p > q) {
		cin.clear();
		cin.ignore(9999, '\n');
		cin >> p;
		cin >> q;
	}
	if (p < 0 && p == q) return 0;
	cout << rec(p, q);
}
*/

#include <iostream>
using namespace std;

int rec(int p, int q)
{
    if (p == q + 1) return 0;
    if (p == 0) return 0 + rec(p + 1, q);
    if (p % 10 > 0) return  p % 10 + rec(p + 1, q);
    return p / 10 + rec(p + 1, q);
}

int main()
{
    int p, q, w = 0;
    int* a = (int*)malloc(w * sizeof(int));
    for (;;) {
        a = (int*)realloc(a, ++w * sizeof(int));
        cin >> p;
        cin >> q;
        while (cin.fail() || p > q) {
            cin.clear();
            cin.ignore(9999, '\n');
            cin >> p;
            cin >> q;
        }
        if (p < 0 && p == q) {
            cout << "\n";
            for (int i = 0; i < w - 1; i++)
                cout << a[i] << "\n";
            return 0;
        }
        a[w - 1] = rec(p, q);
    }
}