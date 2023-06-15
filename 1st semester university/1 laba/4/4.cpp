//Лабораторная 1, задача 4. Выполнена: Климкович Н. В.

//Определить время падения камня на поверхность земли с высоты h.

#include <iostream>
using namespace std;
int main()
{
	double h;
	cout << "h = ";
	cin >> h;
	cout << "t = " << sqrt(h*2/9.8) << " sec";
	return 0;
}