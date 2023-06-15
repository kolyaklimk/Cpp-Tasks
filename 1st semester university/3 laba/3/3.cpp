//Лабораторная 3, задача 3. Выполнена: Климкович Н. В.

/*Использовать for.
Найти значение функции y=sin(x)-cos(x)
на отрезке [A,B] в точках X(i)=A+i*H,
где H=(B-A)/M, M=20, A=0, B=pi/2.*/

#include <cmath>
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	const double pi = 3.14159265358979323846;
	double y, x, h, b;
	short a = 0, m = 20;
	b = pi / 2;
	h = (b - a) / 20;
	y = 0;
	cout << "Найти значение функции y=sin(x)-cos(x)\n"
		<< "на отрезке [A,B] в точках X(i)=A+i*H,\n"
		<< "где H=(B-A)/M, M=20, A=0, B=pi/2.\n";
	for (int i = 0;; i++) {
		x = (a + i * h);
		y = sin(x) - cos(x);
		if (x > b) return 0;
		cout << "\ny" << i + 1 << " = " << y;
	}
}