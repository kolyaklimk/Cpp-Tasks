//Лабораторная 2, задача 14. Выполнена: Климкович Н. В.

/*Даны действительные числа a, b, c, x, y. Выяснить, пройдёт ли
кирпич с ребрами a, b, c в прямоугольное отверстие со стороны x и y.
просовывать кирпич в отверстие разрешается только так, чтобы каждое из его
было параллельно или перпендикулярно каждый из сторон отверстия.*/

#include <iostream> 
using namespace std;
int main()
{
	double a, b, c, x, y;
	cout << "a = "; cin >> a;
	cout << "b = "; cin >> b;
	cout << "c = "; cin >> c;
	cout << "x = "; cin >> x;
	cout << "y = "; cin >> y;

	while (a <= 0 || b <= 0 || c <= 0 || x <= 0 || y <= 0) {
		cout << "Enter the correct value\n";
		cout << "\na = "; cin >> a;
		cout << "b = "; cin >> b;
		cout << "c = "; cin >> c;
		cout << "x = "; cin >> x;
		cout << "y = "; cin >> y;
	}

	if (a <= x && b <= y || b <= x && a <= y || c <= x && b <= y || b <= x && c <= y || a <= x && c <= y || c <= x && a <= y)
		cout << "\nThe brick will go through the hole";
	else cout << "\nThe brick will not go through the hole";

	return 0;
}