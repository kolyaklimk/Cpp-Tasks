﻿//Лабораторная 5, задача Доп_3. Выполнена: Климкович Н. В.

/*Пусть f(n) - наибольший нечетный делитель натурального числа n.
По заданному
натуральному n необходимо вычислить значение суммы f(1) + f(2) + ... + f(n).

Входные данные:
Каждая строка содержит одно натуральное число n (n ≤ 109).

Выходные данные:
Для каждого значения n в отдельной строке вывести значение суммы f(1) + f(2) + ... + f(n).*/

#include <iostream>
using namespace std;

unsigned long long rec(unsigned long long a)
{
	if (a == 0) return 0;
	else
		return pow((a + 1) / 2, 2) + rec(a / 2);
}

int main()
{
	unsigned long long a;
	cin >> a;
	while (cin.fail() || a % 2 == 0 || a < 1) {
		cin.clear();
		cin.ignore(9999, '\n');
		cin >> a;
	}
	cout << rec(a);
}