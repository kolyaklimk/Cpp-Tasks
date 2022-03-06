//Лабораторная 2, задача 1. Выполнена: Климкович Н. В.

/*Сможет ли шар радиуса R пройти в ромбообразное отверстие
стороной P и острым углом Q?*/

#include <iostream> 
#include <cmath>
using namespace std;
int main()  
{
	double r, p, q, pi;
	cout << "R = "; cin >> r;
	cout << "P = "; cin >> p;
	cout << "q = "; cin >> q;
	pi = 3.14159265359;

	while (p <= 0 || r <= 0 || q <= 0 || q >= 90) {
		cout << "Enter the correct value\n";
		cout << "\nR = "; cin >> r;
		cout << "P = "; cin >> p;
		cout << "q = "; cin >> q;
	}

	if (r <= p * sin(pi * q / 180) / 2)
		cout << "Yes";
	else cout << "No";

	return 0;
}