//Лабораторная 1, задача 2. Выполнена: Климкович Н. В.

/*Составить программу на языке С++ для расчета соотношения. Исходные
данные ввести с клавиатуры. Вариант – номер по журналу (Вариант №8)*/

#include <iostream> <cmath>
using namespace std;
int main()
{
	double x, d, c, k;

	cout << "x = "; cin >> x;
	cout << "d = ";	cin >> d;
	cout << "c = ";	cin >> c;
	cout << "k = ";	cin >> k;

	cout << "Y = " << log10(x) + x + exp(d) - c * c / k;
	return 0;
}