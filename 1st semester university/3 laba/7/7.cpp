//Лабораторная 3, задача 7. Выполнена: Климкович Н. В.

/*Найти двухзначное число, обладающее тем свойством, что куб
суммы его цифр равен квадрату самого числа.*/

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	for (int a = 1; a < 10; a++) {
		for (int b = 0; b < 10; b++) {
			if (pow(a + b, 3) == pow(10 * a + b, 2)) cout << 10 * a + b;
		}
	}
	cout << " - is a two-digit number,\n"
		<< "that the cube of the sum of its digits\n"
		<< "is equal to the square of the number itself.\n";

		return 0;
}