//Лабораторная 1, задача 3. Выполнена: Климкович Н. В.

/*На вход даны 6 чисел x1, y1; x2, y2; x3, y3 - координаты вершин А, В, С
соответственно. Необходимо вычислить:
1. Длину всех сторон треугольника.
2. Длину всех высот треугольника.
3. Длину всех медиан треугольника.
4. Длину всех биссектрис треугольника.
5. Градусную и радианную меру углов треугольника.
6. Радиусы вписанной и описанной окружностей треугольника.
7. Найти площадь и длину этих окружностей.
8. Площадь и периметр треугольника.
Примечание. Гарантируется существование треугольника с данными
координатами. При выводе чисел необходимо обозначать, какие именно
параметры вы выводите. Площадь треугольника считать минимум 3
способами.*/

#include <iostream> <cmath>
using namespace std;
int main()
{
	double x1, y1, x2, y2, x3, y3;
	const double pi = 3.14159;

	cout << "x1 = "; cin >> x1;
	cout << "y1 = "; cin >> y1;
	cout << "x2 = "; cin >> x2;
	cout << "y2 = "; cin >> y2;
	cout << "x3 = "; cin >> x3;
	cout << "y3 = "; cin >> y3;

	//Длина стороны
	double s1, s2, s3;
	s1 = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	s2 = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
	s3 = sqrt(pow((x3 - x2), 2) + pow((y3 - y2), 2));
	cout << endl << "sides of a triangle:" << endl << "s1 = " << s1 <<endl << "s2 = " << s2 << endl << "s3 = " << s3 << endl;

	//Высота
	double p = (s1 + s2 + s3) / 2;
	double h_ = 2 * sqrt(p * (p - s1) * (p - s2) * (p - s3));
	cout << endl << "heights:" << endl << "h1 = " << h_ / s1 << endl << "h2 = " << h_ / s2 << endl << "h3 = " << h_ / s3 << endl;

	//Медина
	cout << endl << "medians:" << endl << "m1 = " << sqrt(2 * s3 * s3 + 2 * s2 * s2 - s1 * s1) / 2;
	cout << endl << "m2 = " << sqrt(2 * s3 * s3 + 2 * s1 * s1 - s2 * s2) / 2;
	cout << endl << "m3 = " << sqrt(2 * s1 * s1 + 2 * s2 * s2 - s3 * s3) / 2 << endl;

	//Биссектриса
	cout << endl << "bisectors:" << endl << "b1 = " << sqrt(s2 * s3 * p * (p - s1)) / (s2 + s3) * 2;
	cout << endl << "b2 = " << sqrt(s1 * s3 * p * (p - s2)) / (s1 + s3) * 2;
	cout << endl << "b3 = " << sqrt(s2 * s1 * p * (p - s3)) / (s2 + s1) * 2 << endl;

	//Градусная и радианная мера угла
	double r1 = acos((s2 * s2 + s3 * s3 - s1 * s1) / 2 / s2 / s3);
	double r2 = acos((s1 * s1 + s3 * s3 - s2 * s2) / 2 / s1 / s3);
	double r3 = acos((s2 * s2 + s1 * s1 - s3 * s3) / 2 / s2 / s1);
	cout << endl << "radians:" << endl << "r1 = " << r1 << endl << "r2 = " << r2 << endl << "r3 = " << r3 << endl;
	cout << endl << "degrees:" << endl << "d1 = " << r1*180/pi << endl << "d2 = " << r2*180/pi << endl << "d3 = " << r3*180/pi << endl;

	//Радиус
	double r_in = sqrt((p - s1) * (p - s2) * (p - s3) / p);
	double r_de = s1 * s2 * s3 / sqrt(p * (p - s1) * (p - s2) * (p - s3)) / 4;
	cout << endl << "inscribed radius:" << endl << "r = " << r_in << endl;
	cout << endl << "described radius:" << endl << "R = " << r_de << endl;

	//Площадь и длина окружности
	cout << endl << "area R:" << endl << "S_R = " << pi * r_de * r_de << endl;
	cout << endl << "area r:" << endl << "S_r = " << pi * r_in * r_in << endl;
	cout << endl << "length R:" << endl << "C_R = " << pi * r_de * 2 << endl;
	cout << endl << "length r:" << endl << "C_r = " << pi * r_in * 2 << endl;

	//Площадь и периметр треугольника
	cout << endl << "perimeter:" << endl << "P = " << s1 + s2 + s3 << endl;
	cout << endl << "area:" << endl << "S_1 = " << p * r_in << endl;
	cout << "S_2 = " << s1 * s2 * s3 / r_de / 4 << endl;
	cout << "S_3 = " << h_ / 2 << endl;

	return 0;
}