//Лабораторная 5, задача 1. Выполнена: Климкович Н. В.

/*Сформировать двумерный динамический массив-матрицу А размерностью
n x n (n = 10), причем значения aij определить согласно выражению.
Сформировать транспонированную матрицу B = AT.
Определить сумму элементов четных строк и нечетных столбцов для массива-
матрицы А и сумму четных столбцов и нечетных строк для массива-матрицы В. На экран
вывести массивы-матрицы А и В построчно и значения сумм. Использовать функции.*/

#include <iostream>
#include <iomanip>
using namespace std;

void transp(int **a,int **b, int x) {
	for (int q = 0; q < x; q++)
		for (int q1 = 0; q1 < x; q1++)
			b[q][q1] = a[q1][q];
}

void cout_m(int** a, int x, int size) {
	for (int q = 0; q < x; q++) {
		for (int q1 = 0; q1 < x; q1++)
			cout << setw(size) << a[q][q1];
		cout << "\n";
	}
	cout << "\n";
}

int size(int** a, int x) {
	int w, m,m1;
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
	return m1+1;
}

int sum(int** a, int x, int x1, int n) {
	int sum = 0;
	for (int i = x; i < n; i+=2)
		for (int j = x1; j < n; j+=2) {
			sum += a[i][j];
		}
	return sum;
}

void delete_m(int** a, int n) {
	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[]a;
}

int main()
{
	int i, j, z, n = 10;

	//массив А
	int** a = new int*[n];
	for(i = 0; i < n; i++)
		a[i] = new int [n];

	//массив В
	int** b = new int* [n];
	for (i = 0; i < n; i++)
		b[i] = new int[n];

	//ввод значений в массив A
	for (i=1;i<n+1;i++)
		for (j = 1; j < n + 1; j++) {
			if (i <= 5) a[i - 1][j - 1] = 2 * i * j * j - 2 * j;
			else a[i - 1][j - 1] = 3 * i * j - 3;
		}

	z = size(a, n);
	transp(a, b, n);
	cout_m(a, n, z);
	cout_m(b, n, z);

	cout << "\nsum A = " << sum(a, 1, 0, n) << "\nsum B = " << sum(b, 0, 1, n);

	delete_m(a, n);
	delete_m(b, n);
}