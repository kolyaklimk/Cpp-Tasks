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
	long double a, b, ten = 1, ele = 0, s, o;
	int t = 0, minus = 1;	
	string l;
	cin >> a;
	while (cin.fail() || chek_nine(a, a) == -1 || a > 1e15 || a-trunc(a)!=0) {
		cin.clear();
		cin.ignore(9999, '\n');
		cin >> a;
	}
	if (a < 0) {
		minus = -1;
		a *= -1;
	}
	b = to_ten(a, a, 0, 0);
	s = b;
	while (b >= 1) {
		ele += fmod(b, 11) * ten;
		b = trunc(b / 11);
		ten *= 10;
	}
	cout << fixed << ele * minus;
	///////////////////////////////////////////////////////////////////////////////////
	while (s >= 1) {
		o = fmod(s, 11);
		if (o == 10) l += 'A';
		else l += o + '0';
		s = trunc(s / 11);
	}

	for (int j = 0, j1 = l.length() - 1; j < l.length() / 2; j++, j1--)
		swap(l[j], l[j1]);
	if (minus == -1) l.insert(0, "-");
	cout << '\n' << l;
}