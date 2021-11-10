//Лабораторная 5, задача 3.3. Выполнена: Климкович Н. В.

/*Создать двумерный динамический массив вещественных чисел. Определить,
встречаются ли среди них элементы с нулевым значением. Если встречаются такие
элементы, то определить их индексы и общее количество. Переставить элементы этого
массива в обратном порядке и вывести на экран.
Использовать функции.*/

#include <iostream>
#include <iomanip>
using namespace std;

void cin_m(double** a, int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cout << "[" << i << "][" << j << "] = ";
			cin >> a[i][j];
			while (cin.fail()) {
				cin.clear();
				cin.ignore(9999, '\n');
				cout << "[" << i << "][" << j << "] = ";
				cin >> a[i][j];
			}
		}
}

int size(double** a, int x) {
	int w, m, m1;
	w = 0;
	m1 = 0;
	for (int i = 0; i < x; i++)
		for (int j = 0; j < x; j++) {
			w = a[i][j];
			m = 0;
			while (w > 0) {
				w /= 10;
				m++;
			}
			if (m > m1) m1 = m;
		}
	return m1 + 1;
}

void cout_m(double** a, int x, int size) {
	cout << "\n";
	for (int q = 0; q < x; q++) {
		for (int q1 = 0; q1 < x; q1++)
			cout << setw(size) << a[q][q1];
		cout << '\n';
	}
}

void swap_m(double** a, int x) {
	for (int i = 0, i1 = x - 1; i < x; i++, i1--)
		for (int j = 0, j1 = x - 1; j < x; j++, j1--) {
			if (i >= ceil(double(x) / 2) || i == x / 2 && j >= x / 2) break;
			swap(a[i][j], a[i1][j1]);
		}
}

int main()
{
	int i, j, n, x = 0, y, i1, j1;
	cout << "N = ";
	cin >> n;
	while (cin.fail() || n < 1) {
		cin.clear();
		cin.ignore(9999, '\n');
		cout << "incorrect value, N = ";
		cin >> n;
	}

	double** a = new double* [n];
	for (i = 0; i < n; i++)
		a[i] = new double[n];

	cin_m(a, n);
	cout_m(a, n, size(a, n));

	cout << "\n0: ";
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (a[i][j] == 0) {
				cout << "[" << i << "][" << j << "] ";
				x++;
			}

	cout << "\nAmount: " << x;

	swap_m(a, n);
	cout_m(a, n, size(a, n));
}