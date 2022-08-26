//Лабораторная 3, задача 9. Выполнена: Климкович Н. В.

/*Вычислить. Входные данные таковы, что результат может быть вычислен
без переполнения. Использование вещественной арифметики запрещено.*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>
using namespace std;
int main()
{
	long long a, n, p, x;
	cout << "Sum of numbers: a(0)-2a(1)+2^(n-1)*(-1)^(n-1)*a(n-1)\n"
		<< "Amount of numbers n = ";
	cin >> n;
	p = 0; x = 0;
	srand(time(NULL));
	for (int q = 0; q <= n-1; q++) {
		a = rand()%2+1;
		if (p == 0) x = a;
		else x += a * pow(2 * (-1), q);
		p++;
	}
	cout << x;

	return 0;
}