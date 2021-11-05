//Лабораторная 5, задача 1. Выполнена: Климкович Н. В.

/*Дан двумерный динамический массив целых чисел. Значения элементов данного
массива ввести с клавиатуры. Создать динамический массив из элементов,
расположенных в четных столбцах данного массива и имеющих нечетное значение.
Вычислить среднее арифметическое элементов динамического массива.
Вывести результат на экран. Использовать функции.*/

#include <iostream>
#include <iomanip>
using namespace std;

void cin_m(int** a, int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cout << "[" << i << "][" << j << "] = ";
			cin >> a[i][j];
		}
}

int size(int** a, int x) {
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

void cout_m(int** a, int x, int x1, int size) {
	cout << "\n\n";
	for (int q = 0; q < x; q++) {
		for (int q1 = 0; q1 < x1; q1++)
			cout << setw(size) << a[q][q1];
		cout << '\n';
	}
	cout << '\n';
}

int main()
{
	int i, j, n, x, y;
	cout << "N = ";
	cin >> n;
	x = n / 2;

	int** a = new int* [n];
	for (i = 0; i < n; i++)
		a[i] = new int[n];

	cin_m(a, n);
	cout_m(a, n, n, size(a, n));

	int** b = new int* [n];
	for (i = 0; i < n; i++)
		b[i] = new int[x];

	int m = 0, m1 = 0;
	for (int q = 0; q < n; q++)
		for (int q1 = 1; q1 < n; q1 += 2) {
			if (a[q][q1] % 2 != 0) {
				b[m][m1] = a[q][q1];
				if (m1 + 1 < x) m1++;
				else {
					m++;
					m1 = 0;
				}
			}
			else {
				b[m][m1] = 0;
				if (m1 + 1 < x) m1++;
				else {
					m++;
					m1 = 0;
				}
			}
		}

	cout_m(b, n, x, size(a, n));

	m = 0; m1 = 0;
	for (int q = 0; q < n; q++)
		for (int q1 = 0; q1 < x; q1++) {
			if (b[q][q1] != 0) m++;
			m1 += b[q][q1];
		}

	cout << "Average = " << m1 / m;
}