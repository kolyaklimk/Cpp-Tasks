//Лабораторная 2, задача 11. Выполнена: Климкович Н. В.

/*Определить, какая из двух фигур (круг или квадрат) имеет большую
площадь. Известно, что сторона квадрата равна a, радиус круга r. Библиотеку
<cmath> использовать запрещено.*/

#include <iostream>
using namespace std;
int main()
{
	double a, r, p;
	cout << "a = "; cin >> a;
	cout << "r = "; cin >> r;
	p = 3.14159265359;

	while (a <= 0 || r <= 0) {
		cout << "Enter the correct value\n";
		cout << "\na = "; cin >> a;
		cout << "r = "; cin >> r;
	}

	if (a * a == p * r * r) cout << "The area of the square and the circle are equal";
	else if (a * a > p * r * r) cout << "The area of the square is greater than the area of the circle";
	else cout << "The area of the circle is greater than the area of the square";

	return 0;
}