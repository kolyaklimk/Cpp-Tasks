//Лабораторная 2, задача 4. Выполнена: Климкович Н. В.

/*Дан квадрат с вершинами в точках (0, 0), (0, k), (k, k), (k, 0). Вычислите
наименьшее из расстояний от точки с координатами (x, y), лежащей внутри
квадрата, до сторон данного квадрата. Координаты вещественные. Если точка
лежит за пределами квадрата, выведите сообщение об этом и расстояние до
ближайшей стороны квадрата.*/

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	double k, x, y, in, y1, x1, o;
	cout << "K = "; cin >> k;
	if (k == 0) { 			// квадрат не существует
		cout << "\nSquare doesn't exist"; 
		exit(0); 
	}
	cout << "X = "; cin >> x; 
	cout << "Y = "; cin >> y;

	if (k < 0) {			// если k<0
		k = fabs(k); 
		x += k; 
		y += k; 
	}
	in = min(min((k - y), y), min((k - x), x));

	if (in == 0) { 			// точка на стороне
		cout << "\nPoint is on the side of the square"; 
		exit(0); 
	}
	cout << "\nSmallest distance to the side of a square: ";

	if (x <= k && x >= 0 && y <= k && y >= 0) cout << in;	  	// внутри
	else {       // вокруг
		x1 = x; y1 = y;
		if (y < 0) y1 = fabs(y) + k;
		if (x < 0) x1 = fabs(x) + k;
		if (x1 > k && y1 > k) cout << sqrt(pow((x1 - k), 2) + pow((y1 - k), 2));		// угол
		else {			// предел четвертей
			if (y <= k && x <= 0 && y >= 0) cout << fabs(x);
			else if (y <= 0 && x <= k && x >= 0) cout << fabs(y);
			else cout << fabs(max(fabs(y), fabs(x)) - k);
		}
		cout << "\nThe point lies outside the square.";
	}
	return 0;
}