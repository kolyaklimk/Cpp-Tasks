//Лабораторная 7, задача 6. Выполнена: Климкович Н. В.

/*Пусть S(x) - это сумма цифр числа x, записанного в десятичной
счисления. Например, S(5) = 5, S(10) = 1, S(322) = 7.

Мы будем называть число х интересным, если S(x+1) < S(x). В каждом
тесте вам будет дано одно число n. Ваша задача посчитать количество
чисел x таких, что 1 <= x <= n и x - итересное.

Входные данные:
Первая строка содержит одно ценое число t (1 <= t <= 1000) - количество
наборов входных данных.
Далее следует t строк, i-я строка содержит одно целое число n (1 <= n <= 10^9)
для i-го набора входных данных.

Выходные данные:
Выведите t целых чисел, i-у число должно быть ответом
на i-й набор входных данных.*/

#include <iostream>
#include <cmath>
using namespace std;

void sum(double& n) {
	double buf = n, buf1 = 0;
	while (n >= 1) {
		buf = trunc(buf / 10) * 10;
		buf1 += n - buf;
		buf /= 10;
		n = trunc(n / 10);
	}
	n = buf1;
}

int main()
{
	int t;
	double n, n1, n2, tt;
	cin >> t;
	while (cin.fail() || t < 1 || t > 1000) {
		cin.clear();
		cin.ignore(9999, '\n');
		cout << "incorrect value, t = ";
		cin >> t;
	}
	double* j = new double[t];
	for (int a = 0; a < t; a++) {
		tt = 0;
		cin >> n;
		while (cin.fail() || n < 1 || n > 1e9) {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "incorrect value, n = ";
			cin >> n;
		}
		for (double b = 1; b <= n; b++) {
			//cout << b << '\n';
			n1 = b + 1;
			n2 = b;
			sum(n1);
			sum(n2);
			if (n1 < n2) tt++;
		}
		j[a] = tt;
	}
	cout << "\n\n";
	for (int g = 0; g < t; g++) {
		cout << j[g] << '\n';
	}
}