//Лабораторная 3, задача 4. Выполнена: Климкович Н. В.

/*Вычислить сумму четных чисел на промежутке от 1 до числа,
введенного пользователем:
4.1 С использованием цикла;
4.2 Без использования цикла.*/

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	long double sum, a;
	cout << "The sum of even numbers in the range from 1 to x.\nx = ";
	cin >> a;
	while (a < 1 || a != round(a) || cin.fail())
	{
		cout << "\nIncorrect value, x = ";
		cin >> a;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(9999, '\n');
			cin >> a;
		}
	}
	sum = 0;
	for (long i = 2; i <= a; i += 2) sum += i;
	cout << "Using a loop, sum = " << sum;

	if (round(a/2) - a/2 != 0) a--;
	sum = (2 + a) / 2 * ((a - 2) / 2 + 1);
	cout << "\nWithout using a loop, sum = " << sum;

	return 0;
}