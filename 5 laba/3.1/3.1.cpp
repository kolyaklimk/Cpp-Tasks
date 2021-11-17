//Лабораторная 5, задача 3.1. Выполнена: Климкович Н. В.

/*Дан двумерный динамический массив целых чисел А размерностью n  k .
Размерность массива (n = 5, k = 6) ввести с клавиатуры. Значения элементов массива
ввести с клавиатуры. Создать динамический массив из элементов, расположенных на
главной диагонали матрицы и имеющих четное значение. Вычислить произведение
элементов динамического массива.
Созданный массив и результат произведения вывести на экран.
Использовать функции.*/

#include <iostream>
#include <iomanip>
using namespace std;

void cin_m(int** a, int n, int k) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < k; j++) {
			cout << "[" << i << "][" << j << "] = ";
			cin >> a[i][j];
			while (cin.fail() || a[i][j]>INT_MAX-4) {
				cin.clear();
				cin.ignore(9999, '\n');
				cout << "[" << i << "][" << j << "] = ";
				cin >> a[i][j];
			}
		}
}

int size(int** a, int x, int x1) {
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
	cout << "\n";
	for (int q = 0; q < x; q++) {
		for (int q1 = 0; q1 < x1; q1++)
			cout << setw(size) << a[q][q1];
		cout << '\n';
	}
}

int main()
{
	int i, j, q1, q, g, g1, t;
	float n, k;
	int* y = 0;
	cout << "n = ";
	cin >> n;
	cout << "k = ";
	cin >> k;
	while (cin.fail() || n < 2 || k < 2) {
		cin.clear();
		cin.ignore(9999, '\n');
		cout << "incorrect value, n = ";
		cin >> n;
		cout << "k = ";
		cin >> k;
	}
	int* b = new int[max(n, k)];
	int** a = new int* [n];
	for (i = 0; i < n; i++)
		a[i] = new int[k];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < k; j++)
			a[i][j] = INT_MAX-2;

	cin_m(a, n,k);
	cout_m(a, n, k, size(a, n,k));

	if (k > n) {
		g = ceil(k / n);
		g1 = g;
		for (q = 0; q < n; q++) {
			for (q1 = g; q1 < k; q1++)a[q][q1] = INT_MAX - 2;
			g += g1;
		}
	}
	else {
		g1 = ceil(n / k);
		g = n-g1;
		for (q1 = k; q1 >= 0; q1--) {
			for (q = g; q >= 0; q--) a[q][q1] = INT_MAX - 2;
			g -= g1;
		}
	}

	//cout_m(a, n, k, size(a, n, k));
	
	i = 0;
	j = 0;
	while (j < k) {
		while (a[i][j] == INT_MAX-2) {
			i++;
			if (a[i][j - 1] % 2 == 0 && a[i][j] == INT_MAX - 2 && b[y - 1] != a[i][j - 1]) {
				b[y] = a[i][j - 1];
				y++;
				t++;
			}
		}
		if (a[i][j] % 2 == 0) {
			b[y] = a[i][j];
			y++;
			t++;
		}
			j++;
	}
	
	j--;
	i++;
	while (i < n) {
		if (a[i][j] % 2 == 0) {
			b[y] = a[i][j];
			t++;
			y++;
		}
		i++;
	}
	
	cout << "\n\n";
	for (i = 0; i < t; i++)
		cout << b[i] << " ";
}