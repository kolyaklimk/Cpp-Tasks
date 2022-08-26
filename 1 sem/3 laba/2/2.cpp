//Лабораторная 3, задача 2. Выполнена: Климкович Н. В.

/*Использовать do while*/

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int n = 0;
	double e = 0.0001, d = 0, sum = 0;
	cout << "Найти сумму ряда d(n)=(1/2)^n+(1/3)^n, \n"
		<< "где n принимает значения от 1 до бесконечности, с точностью E=10^(-3).";
	do {
		n++;
		d = pow(1.0 / 2, n) + pow(1.0 / 3, n);
		sum += d;
	}
	while (d >= e);
	cout <<"\nСумма ряда d(n) = " << sum;

	return 0;
}