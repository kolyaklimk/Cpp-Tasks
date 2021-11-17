﻿//Лабораторная 5, задача 1. Выполнена: Климкович Н. В.

/*Сформировать двумерный динамический массив-матрицу А размерностью
n x n (n = 10), причем значения aij определить согласно выражению.
Сформировать транспонированную матрицу B = AT.
Определить сумму элементов четных строк и нечетных столбцов для массива-
матрицы А и сумму четных столбцов и нечетных строк для массива-матрицы В. На экран
вывести массивы-матрицы А и В построчно и значения сумм. Использовать функции.

СТАТИЧЕСКАЯ БИБЛИОТЕКА*/

#include <iostream>
#pragma comment(lib, "../x64/Debug/StaticLib1.lib")
#include "../StaticLib1/functions.h"
using namespace std;

int main()
{
	int i, j, z, n;
	cout << "N = ";
	cin >> n;
	while (cin.fail() || n < 1) {
		cin.clear();
		cin.ignore(9999, '\n');
		cin >> n;
	}

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