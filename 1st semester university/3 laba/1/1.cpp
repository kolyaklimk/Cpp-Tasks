//Лабораторная 3, задача 1. Выполнена: Климкович Н. В.

/*Использовать while*/

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
    int i = 1;
	int n = 0, a, b;
	cout << "Найти сумму ряда N=(a(i)-b(i))^2, где i принимает значения от 1 до 30."
		<< "\nЕсли i - нечетное, то a(i)=i, а b(i)=i^2."
		<< "\nЕсли i - четное, то a(i)=i/2, а b(i)=i^3.\n";
	while (i<=30){
		if (i % 2 == 0) {
			a = i / 2;
			b = pow(i, 3);
		}
		else {
			a = i;
			b = pow(i, 2);
		}
		n += pow((a - b), 2);
		i++;
	}
	cout << "\nСумма ряда N = " << n;

	return 0;
}