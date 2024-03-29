﻿//Лабораторная 5, задача 2. Выполнена: Климкович Н. В.

/*Для заданного одномерного массива С из N элементов найти произведение
множителей, вычисляемых по формуле. Рекурсивную функцию
применять каждый раз отдельно для первой трети массива и для остальной части (2/3)
массива. Рекурсивные вызовы заканчивать, когда останется только один или два
элемента.

ДИНАМИЧЕСКАЯ БИБЛИОТЕКА*/

#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	int i, n;
	cout << "N = ";
	cin >> n;
	while (cin.fail() || n < 1) {
		cin.clear();
		cin.ignore(9999, '\n');
		cout << "N = ";
		cin >> n;
	}

	int* a = new int [n];
	
	//ввод значений в массив
	for (i = 0; i < n; i++)
		cin >> a[i];
	while (cin.fail()) {
		cin.clear();
		cin.ignore(9999, '\n');
		cin >> a[i];
	}

	HINSTANCE load;
	load = LoadLibrary(L"Dll1.dll");

	typedef double (*Fun) (int*, int, int, int);

	Fun fun = (Fun)GetProcAddress(load, "fun");

	cout << fun(a, n, 0, n / 3) * fun(a, n, n / 3, n);

	FreeLibrary(load);

	delete[] a;
}