//Лабораторная 2, задача 16. Выполнена: Климкович Н. В.

/*Введены два числа. Выведите их НОД и НОК.*/

#include <iostream> 
#include <cmath> 
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int a, b, x;
	cout << "a = "; cin >> a;
	cout << "b = "; cin >> b;

	a = abs(a); b = abs(b);

	double a_c = a; 
	double b_c = b;

	if (a == 0 && b == 0) cout << "Неверное значение";
	else {
		while (b != 0) {
			x = a % b;
			a = b;
			b = x;
		}
	}

	cout << "НОД = " << a;
	cout << " НОК = " << a_c * b_c / a;

	return 0;
}

