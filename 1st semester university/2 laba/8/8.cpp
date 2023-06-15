//Лабораторная 2, задача 8. Выполнена: Климкович Н. В.

/*Вычислить значение y в зависимости от выбранной функции f(x),
аргумент определяется из поставленного условия. Возможные значения
функции f(x): 2x, x^3, x/3 (выбор осуществляется используя оператор switch).
Предусмотреть вывод сообщений, показывающих, при каком условии и с какой
функцией производились вычисления y.

Вариант 8    sin^2 @(x) + a*cos^5x^3 + c*lnx^2/5
*/

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	double x, a, c, z, y, d, pi;
	int v;
	v = 0;
	pi = 3.14159265359;
	cout << "z = ";  cin >> z;
	cout << "a = ";  cin >> a;
	cout << "c = ";  cin >> c;

	if (z >= 0) x = 2 * z + 1;
	if (z < 0) x = log(z * z - z);

	while (v < 1 || v>3) {
		cout << "\nSelect function values:";
		cout << "\n2x - 1" << "\nx^3 - 2" << "\nx/3 - 3";
		cout << "\noption: ";
		cin >> v;
		switch (v) {
		case 1: x *= 2; break;
		case 2: x = pow(x, 3); break;
		case 3: x /= 3; break;
		default: cout << "Choose one of the options.\n"; break;
		}
	}

	d = x * pi / 180;
	y = pow(sin(d), 2) + a * pow(cos(pow(d, 3)), 5) + c * log(pow(x, 2 / 5.0));

	cout << "\ny = " << y << " at ";
	if (z >= 0) cout << "x = 2z+1 (z >= 0), ";
	if (z < 0) cout << "x = ln(z^2-z) (z < 0), ";

	switch (v) {
	case 1: cout << "f(x) = 2x"; break;
	case 2: cout << "f(x) = x^3"; break;
	case 3: cout << "f(x) = x/3"; break;
	}

	return 0;
}