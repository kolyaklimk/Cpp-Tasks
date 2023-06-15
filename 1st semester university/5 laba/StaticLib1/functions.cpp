#include "functions.h"
#include <iostream>
#include <iomanip>
using namespace std;

void transp(int** a, int** b, int x) {
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

int sum(int** a, int x, int x1, int n) {
	int sum = 0;
	for (int i = x; i < n; i += 2)
		for (int j = x1; j < n; j += 2) {
			sum += a[i][j];
		}
	return sum;
}

void delete_m(int** a, int n) {
	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[]a;
}