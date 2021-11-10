//Лабораторная 5, задача 3.1. Выполнена: Климкович Н. В.

/*Дан двумерный динамический массив целых чисел. Значения элементов данного
массива ввести с клавиатуры. Создать динамический массив из элементов,
расположенных в четных столбцах данного массива и имеющих нечетное значение.
Вычислить среднее арифметическое элементов динамического массива.
Вывести результат на экран. Использовать функции.

3 номер*/

#include <iostream>
#include <iomanip>
using namespace std;

void cin_m(int** a, int n, int k) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < k; j++) {
			cout << "[" << i << "][" << j << "] = ";
			cin >> a[i][j];
			while (cin.fail() || a[i][j]>INT_MAX-2) {
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
	int i, j, y, q1, q, g, g1, t;
	float n, k;
	t = 0;
	y = 0;
	cout << "n = ";
	cin >> n;
	cout << "k = ";
	cin >> k;
	while (cin.fail() || n < 1 || k < 1) {
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
			a[i][j] = INT_MAX-1;

	cin_m(a, n,k);
	cout_m(a, n, k, size(a, n,k));

	if (k > n) {
		g = ceil(k / n);
		g1 = g;
		for (q = 0; q < n; q++) {
			for (q1 = g; q1 < k; q1++)a[q][q1] = INT_MAX - 1;
			g += g1;
		}
	}
	else {
		g1 = ceil(n / k);
		g = n-g1;
		for (q1 = k; q1 >= 0; q1--) {
			for (q = g; q >= 0; q--) a[q][q1] = INT_MAX - 1;
			g -= g1;
		}
	}

	cout_m(a, n, k, size(a, n, k));

	i = 0;
	j = 0;
	while (j < k) {
		while (a[i][j] == INT_MAX-1) {
			i++;
			if (a[i][j - 1] % 2 == 0 && a[i][j] == INT_MAX - 1) {
				b[y] = a[i][j - 1];
				y++;
				t++;
			}
		}
		if (i != 0 && b[y - 1] == a[i][j - 1] && a[i - 1][j] == INT_MAX - 1 && n != k) {
			b[y] = a[i][j - 1];
			y++;
			t++;
		}
		if (a[i][j] % 2 == 0) {
			b[y] = a[i][j];
			y++;
			t++;
		}
			j++;
	}
	
	i = n-1;
	j = k-1;
	if (a[i][j] % 2 == 0 && a[i-1][j] != INT_MAX - 1) {
		b[y] = a[i][j];
		t++;
	}
	
	cout << "\n\n";
	for (i = 0; i < t; i++)
		cout << b[i] << " ";
}