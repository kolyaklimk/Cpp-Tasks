//Лабораторная 7, задача 1. Выполнена: Климкович Н. В.

/*Необходимо разработать программу для перевода чисел из
одной системы счисления в другую. Выполнить два варианта решения
задачи: без использования массивов и с помощью массивов.

9) из девятичной в одиннадцатеричную*/

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

long double chek_nine(long double buf, long double a) {
	if (buf < 1) return 0;
	buf = trunc(buf / 10) * 10;
	if (a - buf == 9) return -1;
	a = trunc(a / 10);
	buf /= 10;
	return chek_nine(buf, a);
}

long double to_ten(long double buf, long double a, long double b, int t) {
	if (buf < 1) return 0;
	buf = trunc(buf / 10) * 10;
	b = (a - buf) * pow(9, t++); 
	a = trunc(a / 10);
	buf /= 10;
	return b + to_ten(buf, a, b, t);
}

int main()
{
	long double a, b = 0, ten = 1, ele = 0;
	int t = 0, minus = 1;
	string s;
	for (;;) {
		cin >> a;
		while (cin.fail() || chek_nine(a, a) == -1) {
			cin.clear();
			cin.ignore(9999, '\n');
			cin >> a;
		}








		if (a < 0) {
			minus = -1;
			a *= -1;
		}
		b = to_ten(a, a, 0, 0);
		while (b >= 1) {
			ele += fmod(b, 11) * ten;
			b = trunc(b / 11);
			ten *= 10;
		}
		cout << fixed << ele * minus;
		return 0;
	}
	///////////////////////////////////////////////////////////////////////////////////
}