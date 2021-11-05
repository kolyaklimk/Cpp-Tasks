//Лабораторная 5, задача Доп_2. Выполнена: Климкович Н. В.

/*Рекурсивная функция задана следующим образом:
Вычислить значение.

Входные данные:
Каждая строка содержит три целых числа: k (0 < k < 1019), n (0 < n < 1019) и t (0 < t < 10).
Последняя строка содержит три нуля и не обрабатывается.

Выходные данные:
Для каждого теста в отдельной строке вывести номер теста и значение x. Формат вывода
приведен в примере.*/

#include <iostream>
using namespace std;

int rec(int n, int r, int k, long double** a)
{
	if (n == 0 && r == 0) {
		return 1;
	}
	if (n > 0 && r >= 0 && r < n * (k - 1) + 1) {
		long double sum = 0.0;
		for (int i = 0; i <= k - 1; i++)
			sum += a[n - 1][r - i;
		return sum;
	}
	return 0;
}

int main()
{
	long double k, n, t, x=0;
	cin >> k;
	cin >> n;
	cin >> t;

	long double** a = new long double* [n];
	for (int i = 0; i < n; i++)
		a[i] = new long double[n * (k - 1)];


	/*
	for (int q = 0; q < n; q++)
		for (int q1 = 0; q1 < n * (k - 1); q1++) {
			a[q][q1] = 0;
			a[q][q1] = rec(n, q1, k, a);
		}
	
	for (int q = 0; q < n; q++) {
		for (int q1 = 0; q1 < n * (k - 1); q1++)
			cout << a[q][q1];
		cout << "\n";
	}
	*/

	for (int q = 0; q < n; q++)
		for (int q1 = 0; q1 < n * (k - 1); q1++) 
			a[q][q1] = 0;

	for (int q = 0; q < n; q++)
		for (int q1 = 0; q1 < n * (k - 1); q1++) {
			a[q][q1] = 0;
			a[q][q1] = rec(q, q1, k, a);
		}

	for (int q = 0; q < n; q++) {
		for (int q1 = 0; q1 < n * (k - 1); q1++) {
			cout << a[q][q1];
			cout << " ";
		}
		cout << "\n";
	}



		/*
	for (int i = 0; i <=n*(k-1); i++)
		x += rec(n, i, k, a);

	//x = rec(n, 0, k, a, 1, 0) /*     / pow(10, k)       ;
	cout << x;
	*/
}